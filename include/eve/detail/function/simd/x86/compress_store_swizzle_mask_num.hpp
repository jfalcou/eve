//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE std::pair<int, bool>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<4>>> mask)
    requires (current_api < avx512) && (sizeof(T) == 2)
  {
    static_assert(top_bits<logical<wide<T, fixed<4>>>>::bits_per_element == 2);
    auto to_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
    return compress_store_swizzle_mask_num(to_bytes);
  }
}
