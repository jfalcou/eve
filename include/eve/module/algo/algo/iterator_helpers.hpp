//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/detail.hpp>

#include <concepts>
#include <compare>
#include <memory>

namespace eve::algo
{
  struct operations_with_distance
  {
    friend auto& operator-=(std::derived_from<operations_with_distance> auto& x, std::ptrdiff_t n) { x += -n; return x; }
    friend auto  operator+ (std::derived_from<operations_with_distance> auto x, std::ptrdiff_t n)  { x += n; return x; }
    friend auto  operator+ (std::ptrdiff_t n, std::derived_from<operations_with_distance> auto x)  { return x + n; }
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

  template <typename T, typename U>
  auto spaceship_helper(T x, U y) {
         if constexpr ( detail::supports_spaceship<T, U>                  ) return x <=> y;
    else if constexpr ( std::contiguous_iterator<T> && std::same_as<T, U> ) return std::to_address(x) <=> std::to_address(y);
  }
}
