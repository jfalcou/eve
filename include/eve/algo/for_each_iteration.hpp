//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/conditional.hpp>

namespace eve::algo
{
  struct for_each_iteration_
  {
    template <typename Traits, typename I, typename S, typename Delegate>
    void operator()(Traits, I f, S l, Delegate& delegate) const
    {
      static constexpr std::ptrdiff_t step = typename I::cardinal{}();

      I precise_l = f + ((l - f) / step * step);

      while (f != precise_l) {
        if (delegate.step(f, eve::ignore_none)) return;
        f += step;
      }

      eve::keep_first ignore{l - precise_l};
      delegate.step(f, ignore);
    }
  } inline constexpr for_each_iteration;
}
