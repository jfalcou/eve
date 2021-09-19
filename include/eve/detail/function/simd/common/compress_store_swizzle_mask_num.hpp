//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/top_bits.hpp>

#include <eve/function/convert.hpp>
#include <eve/function/count_true.hpp>

#include <utility>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE std::pair<int, bool>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<4>>> mask)
  {
    using w_t = wide<T, fixed<4>>;
    using l_t = logical<wide<T>>;

    // can only be for 64 bit numbers on 128 bit register
    if constexpr (has_aggregated_abi_v<w_t>)
    {
      return compress_store_swizzle_mask_num(convert(mask, as<logical<std::uint32_t>>{}));
    }
    else
    {
      static_assert(top_bits<l_t>::bits_per_element == 1);
      int mmask = top_bits{mask}.as_int();
      return {(mmask & 7), (mmask & 8)};
    }
  }

  template<typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<8>>> mask)
  {
    int sum = 0;
    sum += mask.get(0);
    sum += mask.get(1);
    sum += 3 * mask.get(2);
    sum += 3 * mask.get(3);
    sum += 9 * mask.get(4);
    sum += 9 * mask.get(5);
    return std::pair{sum, eve::count_true(mask)};
  }
}
