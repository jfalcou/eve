//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/equivalent.hpp>
#include <eve/detail/wide_forward.hpp>

#include <bit>

namespace eve {
  template <typename V>
  constexpr auto as_equivalent(V val) {
    if constexpr (has_equivalent<V>) {
      static_assert((sizeof(V) == sizeof(as_equivalent_t<V>)) && (alignof(V) == alignof(as_equivalent_t<V>)));
      return std::bit_cast<as_equivalent_t<V>>(val);
    } else {
      return val;
    }
  }

  template <typename T, typename N>
  constexpr auto as_equivalent_inner(wide<T, N> val) {
    if constexpr (has_equivalent<T>) {
      return bit_cast(val, as<wide<as_equivalent_t<T>, N>>{});
    } else {
      return val;
    }
  }
}