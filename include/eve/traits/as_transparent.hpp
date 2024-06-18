//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/transparent.hpp>
#include <eve/detail/wide_forward.hpp>

#include <bit>

namespace eve {
  template <typename V>
  constexpr auto as_transparent_inner(V val) {
    if constexpr (transparent_value<V>) {
      static_assert((sizeof(V) == sizeof(transparent_inner_t<V>)) && (alignof(V) == alignof(transparent_inner_t<V>)));
      return std::bit_cast<transparent_inner_t<V>>(val);
    } else {
      return val;
    }
  }

  template <typename T, typename N>
  constexpr auto as_transparent_inner(wide<T, N> val) {
    if constexpr (transparent_value<T>) {
      return bit_cast(val, as<wide<transparent_inner_t<T>, N>>{});
    } else {
      return val;
    }
  }
}