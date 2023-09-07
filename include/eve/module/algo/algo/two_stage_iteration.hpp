//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::algo
{

namespace detail
{
  struct two_stage_iteration_common
  {
    template<typename Traits, typename I, typename S, typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits, I& f, S l, Delegate& delegate) const
    {
      // does not support unrolling at the moment
      while( true )
      {
        std::ptrdiff_t left_space = delegate.left_for_stage1();
        left_space = std::min(left_space, l - f);
        left_space /= iterator_cardinal_v<I>;

        if( !left_space ) break;
        do {
          if( delegate.step_1(f) ) return true;
          f += iterator_cardinal_v<I>;
        }
        while( --left_space );
      }

      while( f != l )
      {
        if( delegate.step_2(f) ) return true;
        f += iterator_cardinal_v<I>;
      }

      return false;
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct two_stage_iteration_precise_f_l : two_stage_iteration_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    two_stage_iteration_precise_f_l(Traits traits, I f, S l) : traits(traits), base(f), f(f), l(l)
    {
      EVE_ASSERT(((l - f) % iterator_cardinal_v<I> == 0),
                 " len of the range is no divisible by cardinal "
                     << "when `divisible by cardinal is passed`: "
                     << "l - f: " << (l - f)
                     << " iterator_cardinal_v<I>: " << iterator_cardinal_v<I>);
    }

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      main_loop(traits, f, l, delegate);
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct two_stage_iteration_precise_f : two_stage_iteration_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    two_stage_iteration_precise_f(Traits traits, I f, S l) : traits(traits), base(f), f(f), l(l) {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      I precise_l = f + (((l - f) / iterator_cardinal_v<I>)*iterator_cardinal_v<I>);

      if( main_loop(traits, f, precise_l, delegate) ) return;

      if( precise_l == l ) return;

      eve::keep_first ignore {l - precise_l};
      delegate.tail(f, ignore);
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct two_stage_iteration_aligning : two_stage_iteration_common
  {
    Traits                 traits;
    partially_aligned_t<I> base;
    I                      f;
    S                      l;

    two_stage_iteration_aligning(Traits traits, I f, S l)
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
        if( delegate.tail(aligned_f, ignore_first) ) return;

        ignore_first = eve::ignore_first {0};
        aligned_f += iterator_cardinal_v<I>;

        if( main_loop(traits, aligned_f, aligned_l, delegate) ) return;

        if( aligned_l == l ) return;
      }

      eve::ignore_last ignore_last {aligned_l + iterator_cardinal_v<I> - l};
      delegate.tail(aligned_l, ignore_first && ignore_last);
    }
  };

}

struct
{
  template<typename Traits, iterator I, sentinel_for<I> S>
  auto operator()(Traits traits, I f, S l) const
  {
    EVE_ASSERT(f != l, "two_stage_iteration requires a non-empty range");
    if constexpr( !Traits::contains(no_aligning) && !partially_aligned_iterator<I> )
      return detail::two_stage_iteration_aligning {traits, f, l};
    else if constexpr( Traits::contains(divisible_by_cardinal) )
      return detail::two_stage_iteration_precise_f_l {traits, f, l};
    else return detail::two_stage_iteration_precise_f {traits, f, l};
  }
} inline constexpr two_stage_iteration;

}
