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

enum class continue_break_expensive {
  continue_,
  break_,
  expensive,
};

namespace detail
{
  struct for_each_iteration_with_expensive_optional_part_common
  {
      template <typename I, typename S, typename Delegate>
      struct small_steps_lambda
      {
          I& f;
          S& l;
          continue_break_expensive& delegate_reply;
          Delegate& delegate;

          template <int i>
          EVE_FORCEINLINE bool operator()(std::integral_constant<int, i>)
          {
            delegate_reply = delegate.step(f, eve::ignore_none);
            f += iterator_cardinal_v<I>;

            if (delegate_reply != continue_break_expensive::continue_) return true;
            return f == l;
          }
      };

      template<typename Traits, typename I, typename S, typename Delegate>
      EVE_FORCEINLINE continue_break_expensive main_loop(Traits,
                                      I &f,
                                      S l,
                                      Delegate &delegate) const {
        auto delegate_reply = continue_break_expensive::continue_;
        if (f == l) return delegate_reply;

        while (true) {
          if (eve::detail::for_until_<0, 1, get_unrolling<Traits>()>(
            small_steps_lambda<I, S, Delegate>{f, l, delegate_reply, delegate}
          )) {
            return delegate_reply;
          }
        }
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
      continue_break_expensive action;
      while( true )
      {
        action = this->main_loop(traits, f, l, delegate);
        if( action == continue_break_expensive::expensive) {
          if( !delegate.expensive_part() ) {
            continue;
          }
        }
        return;
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
      I precise_l = f + (((l - f) / iterator_cardinal_v<I>)*iterator_cardinal_v<I>);

      continue_break_expensive action = continue_break_expensive::continue_;

    main_loop:
      action = this->main_loop(traits, f, precise_l, delegate);
      if( action == continue_break_expensive::break_ ) return;
      if( action == continue_break_expensive::expensive ) goto expensive_part;

      if( precise_l == l ) return;
      {
        eve::keep_first ignore {l - precise_l};
        action = delegate.step(f, ignore);
      }

      if( action == continue_break_expensive::expensive ) {
        // hack to exit after the `expensive_part` without any extra checks.
        l = precise_l;
        goto expensive_part;
      }
      return;

    expensive_part:
      if( delegate.expensive_part() ) return;
      goto main_loop;
    }
  };

  template<typename Traits, iterator I, sentinel_for<I> S>
  struct for_each_iteration_with_expensive_optional_part_aligning
    : for_each_iteration_with_expensive_optional_part_common
  {
    Traits traits;
    I base;
    I f;
    S l;

    for_each_iteration_with_expensive_optional_part_aligning(Traits traits, I f, S l)
        : traits(traits)
        , base(f.previous_partially_aligned())
        , f(f)
        , l(l)
    {}

    template<typename Delegate> EVE_FORCEINLINE void operator()(Delegate& delegate)
    {
      auto aligned_f = base;
      auto aligned_l = (f + (l - f)).previous_partially_aligned();

      continue_break_expensive action = continue_break_expensive::continue_;

      eve::ignore_first ignore_first {f - aligned_f};

      if( aligned_f != aligned_l )
      {
        action       = delegate.step(aligned_f, ignore_first);
        ignore_first = eve::ignore_first {0};

        if( action == continue_break_expensive::break_ ) return;
        if( action == continue_break_expensive::expensive ) goto expensive_part;
        aligned_f += iterator_cardinal_v<I>;

     main_loop:
        // handles aligned_f == aligned_l
        action = this->main_loop(traits, aligned_f, aligned_l, delegate);
        if( action == continue_break_expensive::break_ ) return;
        if( action == continue_break_expensive::expensive ) goto expensive_part;
      }

      if( aligned_f == l ) { return; }

      {
        eve::ignore_last ignore_last {aligned_l + iterator_cardinal_v<I> - l};
        action = delegate.step(aligned_l, ignore_first && ignore_last);
      }
      if( action == continue_break_expensive::expensive ) {
        l = aligned_l;  // hack that pevents comming here after the expensive part
        goto expensive_part;
      }
      return;

    expensive_part:
      if( delegate.expensive_part() ) return;
      goto main_loop;
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
