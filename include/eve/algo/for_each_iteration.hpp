//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
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
  struct for_each_iteration_
  {
    template <typename Traits, iterator_basics I, sentinel_for<I> S, typename Delegate>
    EVE_FORCEINLINE void operator()(Traits traits, I f, S l, Delegate& delegate) const
      requires (Traits::contains(no_aligning)())
    {
      static constexpr std::ptrdiff_t step = typename I::cardinal{}();

      I precise_l = f + ((l - f) / step * step);

      if (main_loop(traits, f, precise_l, delegate)) return;

      if (precise_l == l) return;

      eve::keep_first ignore{l - precise_l};
      delegate.step(f, ignore);
    }

    template <typename Traits, unaligned_iterator I, sentinel_for<I> S, typename Delegate>
    EVE_FORCEINLINE void operator()(Traits traits, I f, S l, Delegate& delegate) const
      requires (!Traits::contains(no_aligning)())
    {
      static constexpr std::ptrdiff_t step = typename I::cardinal{}();

      auto aligned_f = f.previous_partially_aligned();
      auto aligned_l = (f + (l - f)).previous_partially_aligned();

      eve::ignore_first ignore_first{f - aligned_f};

      if (aligned_f != aligned_l) {
        // first chunk, maybe partial
        if (delegate.step(aligned_f, ignore_first)) return;
        ignore_first = eve::ignore_first{0};
        aligned_f += step;

        if (main_loop(traits, aligned_f, aligned_l, delegate)) return;

        if (aligned_l == l) return;
      }

      eve::ignore_last ignore_last { aligned_l + step - l };
      delegate.step(aligned_l, ignore_first && ignore_last);
    }

  private:

    template <typename Traits, typename I, typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits, I& f, I l, Delegate& delegate) const
      requires(get_unrolling<Traits>() == 1)
    {
      static constexpr std::ptrdiff_t step = typename I::cardinal{}();

      while (f != l) {
        if (delegate.step(f, eve::ignore_none)) return true;
        f += step;
      }

      return false;
    }

    template <typename Traits, typename I, typename Delegate>
    EVE_FORCEINLINE bool main_loop(Traits, I& f, I l, Delegate& delegate) const
      requires(get_unrolling<Traits>() > 1)
    {
      static constexpr std::ptrdiff_t step = typename I::cardinal{}();
      static constexpr std::ptrdiff_t unrolling = get_unrolling<Traits>();

      // In order to optimise for smaller ranges we not only finish but start with
      // single steps as well.
      // This does not matter for really big ranges but for when we hit a tiny range,
      // not doing the full unrolling can be helpful.
      while (true) {
        bool reached_end = false;
        bool should_break = false;

        // single steps
        if( eve::detail::for_until_<0, 1, unrolling>([&](auto) mutable {
              reached_end = (f == l);
              if( reached_end )
                return true;

              should_break = delegate.step(f, eve::ignore_none);
              f += step;
              return should_break;
            }) )
        {
          return should_break;
        }

        std::ptrdiff_t big_steps_count = (l - f) / (step * unrolling);

        while (big_steps_count) {
          std::array<I, unrolling> arr;
          eve::detail::for_<0, 1, unrolling>([&](auto idx) mutable {
            arr[idx()] = f;
            f += step;
          });
          if (delegate.unrolled_step(arr)) return true;
          --big_steps_count;
        }
      }
    }

  } inline constexpr for_each_iteration;
}
