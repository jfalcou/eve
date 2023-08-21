//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve::detail
{
  template<eve::relative_conditional_expr C, typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(vmx_), C c, logical<wide<T, fixed<4>>> mask)
    requires (sizeof(T) == 4)
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return {0, 0};
    else if constexpr ( !C::is_complete                   ) return compress_store_swizzle_mask_num(ignore_none, mask && c.mask(as(mask)));
    else
    {
      using l_t = logical<wide<T, fixed<4>>>;
      using bits_type = typename l_t::bits_type;
      using sbits_type = typename bits_type::rebind<std::int32_t, fixed<4>>;

      sbits_type sbits = bit_cast(mask.bits(), eve::as<sbits_type>{});

      // last element doesn't participate in the mask
      sbits_type elements_bit{0x11, 0x12, 0x14, 0x10};
      sbits &= elements_bit;

      int desc     = sbits_type{vec_sums(sbits.storage(), sbits_type{0}.storage())}.get(3);
      int num      = desc & 0xf;
      int popcount = desc >> 4;
      return {num, popcount};
    }
  }
}
