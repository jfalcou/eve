//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/core.hpp>

namespace eve::algo
{

namespace detail
{
  struct for_each_iteration_with_expensive_optional_part_common
  {
    template<typename Traits, typename I, typename S> auto unroll_l(Traits, I f, S l)
    {
      return eve::unalign(f) + (l - f - get_unrolling<Traits>() * iterator_cardinal_v<I>);
    }

    template<typename Traits, typename I, typename S, typename Delegate>
    EVE_FORCEINLINE bool no_unrolling_loop(Traits, I& f, S l, Delegate& delegate) const
    {
      while( f != l )
      {
        bool check = delegate.step(f, eve::ignore_none);
        f += iterator_cardinal_v<I>;
        if( check ) return check;
      }
      return false;
    }

    template<typename Traits, typename I, typename S, typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits tr, I& f, auto unroll_l, S l, Delegate& delegate) const
    requires(get_unrolling<Traits>() == 1)
    {
      (void)unroll_l;
      return no_unrolling_loop(tr, f, l, delegate);
    }

    template<typename I, typename S, typename Delegate> struct unrolled_steps_lambda
    {
      I&        f;
      Delegate& delegate;

      template<int i> EVE_FORCEINLINE bool operator()(std::integral_constant<int, i>)
      {
        if( delegate.step(f + i * iterator_cardinal_v<I>, eve::ignore_none) )
        {
          f += i * iterator_cardinal_v<I>;
          return true;
        }
        return false;
      }
    };

    template<typename Traits, typename I, typename S, typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits tr, I& f, auto unroll_l, S l, Delegate& delegate) const
    {
      while( f <= unroll_l )
      {
        if( eve::detail::for_until_<0, 1, get_unrolling<Traits>()>(
                unrolled_steps_lambda<I, S, Delegate> {f, delegate}) )
        {
          return true;
        }
        f += get_unrolling<Traits>() * iterator_cardinal_v<I>;
      }

      return no_unrolling_loop(tr, f, l, delegate);
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_with_expensive_optional_part_precise_f_l
      : for_each_iteration_with_expensive_optional_part_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    for_each_iteration_with_expensive_optional_part_precise_f_l(Traits t, I i, S s)
        : traits(t)
        , base(i)
        , f(i)
        , l(s)
    {
      EVE_ASSERT(((l - f) % iterator_cardinal_v<I> == 0),
                 " len of the range is no divisible by cardinal "
                     << "when `divisible by cardinal is passed`: " << "l - f: " << (l - f)
                     << " iterator_cardinal_v<I>: " << iterator_cardinal_v<I>);
    }

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      auto unroll_l = this->unroll_l(traits, f, l);
      goto main_loop;

      while( true )
      {
        // expensive part before main loop should help when expensive part
        // it forms a separate while loop.
        if( delegate.expensive_part() ) return;
      main_loop:
        if( !this->main_loop(traits, f, unroll_l, l, delegate) ) return;
      }
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_with_expensive_optional_part_precise_f
      : for_each_iteration_with_expensive_optional_part_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    for_each_iteration_with_expensive_optional_part_precise_f(Traits t, I i, S s)
        : traits(t)
        , base(i)
        , f(i)
        , l(s)
    {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      I    precise_l = f + (((l - f) / iterator_cardinal_v<I>)*iterator_cardinal_v<I>);
      auto unroll_l  = this->unroll_l(traits, f, l);
      goto main_loop;

    // expensive part before main loop should help when expensive part
    // it forms a separate while loop.
    expensive_part:
      if( delegate.expensive_part() ) return;
    main_loop:
      if( this->main_loop(traits, f, unroll_l, precise_l, delegate) ) { goto expensive_part; }

      if( precise_l == l ) return;
      {
        eve::keep_first ignore {l - precise_l};
        if( !delegate.step(f, ignore) ) { return; }

        // hack to exit after the `expensive_part` without any extra checks.
        l = precise_l;
        goto expensive_part;
      }
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_with_expensive_optional_part_aligning
      : for_each_iteration_with_expensive_optional_part_common
  {
    Traits traits;
    I      base;
    I      f;
    S      l;

    for_each_iteration_with_expensive_optional_part_aligning(Traits t, I i, S s)
        : traits(t)
        , base(i.previous_partially_aligned())
        , f(i)
        , l(s)
    {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      auto aligned_f = base;
      auto aligned_l = (f + (l - f)).previous_partially_aligned();
      auto unroll_l  = this->unroll_l(traits, f, l);

      eve::ignore_first ignore_first {f - aligned_f};

      if( aligned_f != aligned_l )
      {
        {
          bool first_step_res = delegate.step(aligned_f, ignore_first);
          ignore_first        = eve::ignore_first {0};
          aligned_f += iterator_cardinal_v<I>;
          if( !first_step_res ) goto main_loop;
        }

      // expensive part before main loop should help when expensive part
      // it forms a separate while loop.
      expensive_part:
        if( delegate.expensive_part() ) return;
      main_loop:
        // handles aligned_f == aligned_l
        if( this->main_loop(traits, aligned_f, unroll_l, aligned_l, delegate) ) goto expensive_part;
      }

      if( aligned_f == l ) return;
      {
        eve::ignore_last ignore_last {aligned_l + iterator_cardinal_v<I> - l};
        if( !delegate.step(aligned_l, ignore_first && ignore_last) ) return;
        l = aligned_l; // hack that pevents comming here after the expensive part
        goto expensive_part;
      }
    }
  };
}

//================================================================================================
//! @addtogroup algos
//! @{
//!    @var for_each_iteration_with_expensive_optional_part
//!
//!    @brief low level util for writing algorithms. A variation on for_each_iteration that has a
//!    place for work we don't want duplicated in assembly.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/algo.hpp>
//!   @endcode
//!
//!   `for_each_iteration`, even if not unrolled, generates a few copies of the
//!   callback code. For some algorithms we want to move out a piece of callback code
//!   but we still don't want a function call. Think search: we want to move the more
//!   expensive part of validating match outside.
//!
//!   You can find example usage in the search implementation.
//! @}
//================================================================================================
struct
{
  template<typename Traits, iterator I, sentinel_for<I> S>
  auto operator()(Traits traits, I f, S l) const
  {
    EVE_ASSERT(f != l,
               "for_each_iteration_with_expensive_optional_part requires a non-empty range");
    if constexpr( !Traits::contains(no_aligning) && !partially_aligned_iterator<I> )
    {
      return detail::for_each_iteration_with_expensive_optional_part_aligning {traits, f, l};
    }
    else if constexpr( Traits::contains(divisible_by_cardinal) )
    {
      return detail::for_each_iteration_with_expensive_optional_part_precise_f_l {traits, f, l};
    }
    else
    {
      return detail::for_each_iteration_with_expensive_optional_part_precise_f {traits, f, l};
    }
  }
} inline constexpr for_each_iteration_with_expensive_optional_part;

}
