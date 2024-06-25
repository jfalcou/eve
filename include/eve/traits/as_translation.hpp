//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/translation.hpp>
#include <eve/detail/wide_forward.hpp>

#include <bit>

namespace eve {
  template <typename V>
  constexpr auto translate(V val) {
    if constexpr (has_plain_translation<V>) {
      static_assert((sizeof(V) == sizeof(translate_t<V>)) && (alignof(V) == alignof(translate_t<V>)));
      return std::bit_cast<translate_t<V>>(val);
    } else {
      return val;
    }
  }

  template <typename T, typename N>
  constexpr auto translate(wide<T, N> val) {
    if constexpr (has_plain_translation<T>) {
      return bit_cast(val, as<wide<translate_t<T>, N>>{});
    } else {
      return val;
    }
  }
}
