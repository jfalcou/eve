//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>

#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/count_true.hpp>

#include <utility>

namespace eve::detail
{
  template<eve::relative_conditional_expr C, typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), C c, logical<wide<T, fixed<4>>> mask)
  {
    using w_t = wide<T, fixed<4>>;
    using l_t = logical<wide<T>>;

    // can only be for 64 bit numbers on 128 bit register
    if constexpr (has_aggregated_abi_v<w_t>)
    {
      return compress_store_swizzle_mask_num(c, convert(mask, as<logical<std::uint32_t>>{}));
    }
    else
    {
      static_assert(top_bits<l_t>::bits_per_element == 1);
      int mmask = top_bits{mask, c}.as_int();
      return {(mmask & 7), std::popcount(static_cast<std::uint32_t>(mmask))};
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

  template<typename T>
  EVE_FORCEINLINE auto
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<16>>> mask)
  {
    auto [l, h] = mask.slice();
    auto [l_num, l_count] = compress_store_swizzle_mask_num(l);
    auto [h_num, h_count] = compress_store_swizzle_mask_num(h);

    struct res {
      int l_num;
      int l_count;
      int h_num;
      int h_count;
    };

    return res{l_num, l_count, h_num, h_count};
  }
}
