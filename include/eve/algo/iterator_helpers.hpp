//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/concepts.hpp>

#include <compare>

namespace eve::algo
{
  struct forward_to_unaligned;

  namespace detail
  {

  template <typename I1, typename I2>
  concept should_enable_forward_to_unaligned = (std::derived_from<I1, forward_to_unaligned> ||
                                                std::derived_from<I2, forward_to_unaligned>) &&
                                                same_unaligned_iterator<I1, I2>;
  }

  struct operations_with_distance
  {
    friend auto operator<=>(operations_with_distance const&, operations_with_distance const&) = default;

    friend auto& operator-=(std::derived_from<operations_with_distance> auto& x, std::ptrdiff_t n) { x += -n; return x; }
    friend auto  operator+ (std::derived_from<operations_with_distance> auto x, std::ptrdiff_t n)  { x += n; return x; }
    friend auto  operator- (std::derived_from<operations_with_distance> auto x, std::ptrdiff_t n)  { x -= n; return x; }
  };

  struct forward_to_unaligned
  {
    friend auto operator<=>(forward_to_unaligned const&, forward_to_unaligned const&) = default;

    template <typename T, typename U>
    friend bool operator==(T const& x, U const& y) requires detail::should_enable_forward_to_unaligned<T, U>
    {
      return x.unaligned() == y.unaligned();
    }

    template <typename T, typename U>
    friend auto operator<=>(T const& x, U const& y) requires detail::should_enable_forward_to_unaligned<T, U>
    {
      return x.unaligned() <=> y.unaligned();
    }

    template <typename T, typename U>
    friend std::ptrdiff_t operator-(T const& x, U const& y) requires detail::should_enable_forward_to_unaligned<T, U>
    {
      return x.unaligned() - y.unaligned();
    }
  };
}
