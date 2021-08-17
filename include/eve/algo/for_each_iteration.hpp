//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/traits.hpp>
#include <eve/algo/concepts.hpp>

#include <eve/assert.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/meta.hpp>

#include <array>

namespace eve::algo
{
  namespace detail
  {
    struct for_each_iteration_common
    {
      template<typename Traits, typename I, typename Delegate>
      EVE_FORCEINLINE bool main_loop(Traits, I &f, I l, Delegate &delegate) const
          requires(get_unrolling<Traits>() == 1)
      {
        static constexpr std::ptrdiff_t step = typename I::cardinal {}();

        while( f != l )
        {
          if( delegate.step(f, eve::ignore_none, eve::index<0>) )
            return true;
          f += step;
        }

        return false;
      }

      template <typename I, std::ptrdiff_t step, typename Delegate>
      struct small_steps_lambda
      {
          bool& should_break;
          I& f;
          I& l;
          Delegate& delegate;

          template <int i>
          EVE_FORCEINLINE bool operator()(std::integral_constant<int, i>)
          {
            if (f == l) return true;

            should_break = delegate.step(f, eve::ignore_none, eve::index<i>);
            f += step;
            return should_break;
          }
      };

      template<typename Traits, typename I, typename Delegate>
      EVE_FORCEINLINE bool main_loop(Traits, I &f, I l, Delegate &delegate) const
          requires(get_unrolling<Traits>() > 1)
      {
        static constexpr std::ptrdiff_t step      = typename I::cardinal {}();
        static constexpr std::ptrdiff_t unrolling = get_unrolling<Traits>();

        // In order to optimise for smaller ranges we not only finish but start with
        // single steps as well.
        // This does not matter for really big ranges but for when we hit a tiny range,
        // not doing the full unrolling can be helpful.
        while( true )
        {
          // single steps
          bool should_break = false;

          if( eve::detail::for_until_<0, 1, unrolling>(
                  small_steps_lambda<I, step, Delegate> {should_break, f, l, delegate}) )
          {
            return should_break;
          }

          std::ptrdiff_t big_steps_count = (l - f) / (step * unrolling);

          while( big_steps_count )
          {
            std::array<I, unrolling> arr;
            eve::detail::for_<0, 1, unrolling>([&](auto idx) mutable {
              arr[idx()] = f;
              f += step;
            });
            if( delegate.unrolled_step(arr) )
              return true;
            --big_steps_count;
          }
        }
      }
    };

    template <typename Traits, iterator I, sentinel_for<I> S>
    struct for_each_iteration_precise_f_l : for_each_iteration_common
    {
      Traits traits;
      I base;
      I f;
      S l;

      for_each_iteration_precise_f_l(Traits traits, I f, S l) :
        traits(traits), base(f), f(f), l(l)
      {
        [[maybe_unused]] static constexpr std::ptrdiff_t step =
          typename I::cardinal {}();
        EVE_ASSERT(((l - f) % step == 0),
          " len of the range is no divisible by cardinal " <<
          "when `divisible by cardinal is passed`: " <<
          "l - f: " << (l - f) << " step: " << step);
      }

      template <typename Delegate>
      EVE_FORCEINLINE void operator()(Delegate& delegate)
      {
        main_loop(traits, f, l, delegate);
      }
    };

    template <typename Traits, iterator I, sentinel_for<I> S>
    struct for_each_iteration_precise_f : for_each_iteration_common
    {
      Traits traits;
      I base;
      I f;
      S l;

      for_each_iteration_precise_f(Traits traits, I f, S l) :
        traits(traits), base(f), f(f), l(l) {}

      template <typename Delegate>
      EVE_FORCEINLINE void operator()(Delegate& delegate)
      {
        static constexpr std::ptrdiff_t step = typename I::cardinal{}();

        I precise_l = f + ((l - f) / step * step);

        if (main_loop(traits, f, precise_l, delegate)) return;

        if (precise_l == l) return;

        eve::keep_first ignore{l - precise_l};
        delegate.step(f, ignore, eve::index<0>);
      }
    };

    template <typename Traits, iterator I, sentinel_for<I> S>
    struct for_each_iteration_aligning : for_each_iteration_common
    {
      Traits traits;
      partially_aligned_t<I> base;
      I f;
      S l;

      for_each_iteration_aligning(Traits traits, I f, S l) :
        traits(traits), base(f.previous_partially_aligned()), f(f), l(l) {}

      template<typename Delegate>
      EVE_FORCEINLINE void operator()(Delegate &delegate)
      {
        static constexpr std::ptrdiff_t step = typename I::cardinal {}();

        auto aligned_f = base;
        auto aligned_l = (f + (l - f)).previous_partially_aligned();

        eve::ignore_first ignore_first {f - aligned_f};

        if( aligned_f != aligned_l )
        {
          // first chunk, maybe partial
          if( delegate.step(aligned_f, ignore_first, eve::index<0>) )
            return;
          ignore_first = eve::ignore_first {0};
          aligned_f += step;

          if( main_loop(traits, aligned_f, aligned_l, delegate) )
            return;

          if( aligned_l == l )
            return;
        }

        eve::ignore_last ignore_last {aligned_l + step - l};
        delegate.step(aligned_l, ignore_first && ignore_last, eve::index<0>);
      }
    };
  }

  struct
  {
    template <typename Traits, iterator I, sentinel_for<I> S>
    auto operator()(Traits traits, I f, S l) const
    {
      EVE_ASSERT(f != l, "for_each_iteration requires a non-empty range");
           if constexpr (!Traits::contains(no_aligning))          return detail::for_each_iteration_aligning{traits, f, l};
      else if constexpr (Traits::contains(divisible_by_cardinal)) return detail::for_each_iteration_precise_f_l{traits, f, l};
      else                                                        return detail::for_each_iteration_precise_f{traits, f, l};
    }

  } inline constexpr for_each_iteration;
}
