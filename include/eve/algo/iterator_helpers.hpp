//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <compare>

namespace eve::algo
{
  struct operations_with_distance
  {
    friend auto operator<=>(operations_with_distance const&, operations_with_distance const&) = default;

    friend auto& operator-=(std::derived_from<operations_with_distance> auto& x, std::ptrdiff_t n) { x += -n; return x; }
    friend auto  operator+ (std::derived_from<operations_with_distance> auto x, std::ptrdiff_t n)  { x += n; return x; }
    friend auto  operator- (std::derived_from<operations_with_distance> auto x, std::ptrdiff_t n)  { x -= n; return x; }

    friend auto& operator++(std::derived_from<operations_with_distance> auto& x)  { x += 1; return x; }
    friend auto  operator++(std::derived_from<operations_with_distance> auto& x, int)  {
      auto tmp = x;
      ++x;
      return tmp;
    }

    friend auto& operator--(std::derived_from<operations_with_distance> auto& x)  { x -= 1; return x; }
    friend auto  operator--(std::derived_from<operations_with_distance> auto& x, int)  {
      auto tmp = x;
      --x;
      return tmp;
    }
  };
}
