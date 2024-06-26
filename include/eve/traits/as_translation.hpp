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

namespace eve
{
  template <typename V>
  constexpr auto translate(V val)
  {
    if constexpr (has_plain_translation<element_type_t<V>>)
    {
      using type = as<wide<translate_t<element_type_t<V>>, cardinal_t<V>>>;

      if constexpr (simd_value<V>)  return bit_cast(val, type{});
      else                          return std::bit_cast<translate_t<V>>(val);
    }
    else                            return val;
  }
}
