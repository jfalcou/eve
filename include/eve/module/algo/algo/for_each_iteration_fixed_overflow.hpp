//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/for_each_iteration.hpp>

namespace eve::algo
{
namespace detail
{
  struct for_each_iteration_fixed_overflow_common
  {
    template<std::ptrdiff_t needsBefore,
             std::ptrdiff_t needsAfter,
             typename Traits,
             typename I,
             typename S,
             typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits, I overflow_base, I& f, S l, Delegate& delegate) const
    requires(get_unrolling<Traits>() == 1)
    {
      static_assert(get_overflow<Traits>() % iterator_cardinal_v<I> == 0);
      static_assert(get_overflow<Traits>() >= iterator_cardinal_v<I>
                                                  * (1 + std::max(needsBefore, needsAfter)));

      while( f != l )
      {
        // min(l, overflow_base + get_overflow<Traits>()) but without UB
        I cur_l = f + std::min(l - f, get_overflow<Traits>() - (f - overflow_base));

        while( f != cur_l )
        {
          if( delegate.step(f, eve::ignore_none, eve::index<0>) ) return true;
          f += iterator_cardinal_v<I>;
        }

        bool reached_end    = f == l;
        bool needs_one_more = needsAfter && (f - overflow_base) == get_overflow<Traits>();

        if( !reached_end || needs_one_more )
        {
          delegate.overflow(f);
          overflow_base = f;
        }
      }

      return false;
    }

    template<std::ptrdiff_t needsBefore,
             std::ptrdiff_t needsAfter,
             typename Traits,
             typename I,
             typename S,
             typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits, I overflow_base, I& f, S l, Delegate& delegate) const
    requires(get_unrolling<Traits>() > 1)
    {
      static constexpr std::ptrdiff_t unrolling = get_unrolling<Traits>();
      static_assert(get_overflow<Traits>() % iterator_cardinal_v<I> == 0);
      static_assert(get_overflow<Traits>()
                    >= iterator_cardinal_v<I> * (unrolling + std::max(needsBefore, needsAfter)));

      // In order to optimise for smaller ranges we not only finish but start with
      // single steps as well.
      // This does not matter for really big ranges but for when we hit a tiny range,
      // not doing the full unrolling can be helpful.
      while( true )
      {
        // single steps
        bool should_break = false;

        if( eve::detail::for_until_<0, 1, unrolling>(
                for_each_iteration_common::small_steps_lambda<I, S, Delegate> {
                    should_break, f, l, delegate}) )
        {
          return should_break;
        }

        std::ptrdiff_t big_steps_count =
            std::min(l - f, get_overflow<Traits>() - (f - overflow_base))
            / (iterator_cardinal_v<I> * unrolling);

        while( big_steps_count )
        {
          std::array<I, unrolling> arr;
          eve::detail::for_<0, 1, unrolling>(
              [&](auto idx) mutable
              {
                arr[idx()] = f;
                f += iterator_cardinal_v<I>;
              });
          if( delegate.unrolled_step(arr) ) return true;
          --big_steps_count;
        }

        bool reached_end = (l - f) < unrolling * iterator_cardinal_v<I>;
        bool needs_one_more =
            get_overflow<Traits>()
                - (needsAfter + unrolling) * iterator_cardinal_v<I> < (f - overflow_base);

        if( !reached_end || needs_one_more )
        {
          delegate.overflow(f);
          overflow_base = f;
        }
      }
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_fixed_overflow_precise_f_l : for_each_iteration_fixed_overflow_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    for_each_iteration_fixed_overflow_precise_f_l(Traits traits, I f, S l)
        : traits(traits)
        , base(f)
        , f(f)
        , l(l)
    {
      EVE_ASSERT(((l - f) % iterator_cardinal_v<I> == 0),
                 " len of the range is no divisible by cardinal "
                     << "when `divisible by cardinal is passed`: "
                     << "l - f: " << (l - f)
                     << " iterator_cardinal_v<I>: " << iterator_cardinal_v<I>);
    }

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      main_loop<0, 0>(traits, base, f, l, delegate);
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_fixed_overflow_precise_f : for_each_iteration_fixed_overflow_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    for_each_iteration_fixed_overflow_precise_f(Traits traits, I f, S l)
        : traits(traits)
        , base(f)
        , f(f)
        , l(l)
    {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      I precise_l = f + (((l - f) / iterator_cardinal_v<I>)*iterator_cardinal_v<I>);

      if( main_loop<0, 1>(traits, base, f, precise_l, delegate) ) return;

      if( precise_l == l ) return;

      eve::keep_first ignore {l - precise_l};
      delegate.step(f, ignore, eve::index<0>);
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_fixed_overflow_aligning : for_each_iteration_fixed_overflow_common
  {
    Traits                 traits;
    partially_aligned_t<I> base;
    I                      f;
    S                      l;

    for_each_iteration_fixed_overflow_aligning(Traits traits, I f, S l)
        : traits(traits)
        , base(f.previous_partially_aligned())
        , f(f)
        , l(l)
    {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      auto aligned_f = base;
      auto aligned_l = (f + (l - f)).previous_partially_aligned();

      eve::ignore_first ignore_first {f - aligned_f};

      if( aligned_f != aligned_l )
      {
        // first chunk, maybe partial
        if( delegate.step(aligned_f, ignore_first, eve::index<0>) ) return;
        ignore_first = eve::ignore_first {0};
        aligned_f += iterator_cardinal_v<I>;

        if( main_loop<1, 1>(traits, base, aligned_f, aligned_l, delegate) ) return;

        if( aligned_l == l ) return;
      }

      eve::ignore_last ignore_last {aligned_l + iterator_cardinal_v<I> - l};
      delegate.step(aligned_l, ignore_first && ignore_last, eve::index<0>);
    }
  };
}

struct
{
  template<typename Traits, iterator I, sentinel_for<I> S>
  auto operator()(Traits traits, I f, S l) const
  {
    EVE_ASSERT(f != l, "for_each_iteration_fixed_overflow requires a non-empty range");
    if constexpr( !Traits::contains(no_aligning) && !partially_aligned_iterator<I> )
      return detail::for_each_iteration_fixed_overflow_aligning {traits, f, l};
    else if constexpr( Traits::contains(divisible_by_cardinal) )
      return detail::for_each_iteration_fixed_overflow_precise_f_l {traits, f, l};
    else return detail::for_each_iteration_fixed_overflow_precise_f {traits, f, l};
  }
} inline constexpr for_each_iteration_fixed_overflow;

} // namespace eve::algo
