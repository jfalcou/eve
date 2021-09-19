//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve::detail
{
  // FIX-#965: most of this should be in reduce, except for 64 bits on arm-v7
  template <std::unsigned_integral T>
  EVE_FORCEINLINE T sum4(wide<T, eve::fixed<4>> v)
  {
    if constexpr ( current_api >= asimd )
    {
           if constexpr ( sizeof(T) == 1 ) return vaddv_u8 (v);
      else if constexpr ( sizeof(T) == 2 ) return vaddv_u16(v);
      else if constexpr ( sizeof(T) == 4 ) return vaddvq_u32(v);
      else if constexpr ( sizeof(T) == 8 )
      {
        // aggregated
        auto [l, h] = v.slice();
        l           = vaddq_u64(l, h);
        return vaddvq_u64(l);
      }
    }
    else
    {
      if constexpr( sizeof(T) == 1 )
      {
        v = vpadd_u8(v, v);
        v = vpadd_u8(v, v);
        return v.get(0);
      }
      else if constexpr( sizeof(T) == 2 )
      {
        v = vpadd_u16(v, v);
        v = vpadd_u16(v, v);
        return v.get(0);
      }
      else if constexpr( sizeof(T) == 4 )
      {
        // No usable horrisontal add for 4 ints
        // (the long one does not do it, because unclear
        // what to do with uint64x2
        auto [l, h] = v.slice();

        l = vadd_u32(l, h);
        l = vpadd_u32(l, h);
        return l.get(0);
      }
      // aggregated
      else if constexpr( sizeof(T) == 8 )
      {
        auto [l, h]       = v.slice();
        l                 = vaddq_u64(l, h);
        uint32x2_t halved = vqmovn_u64(l);
        halved            = vpadd_u32(halved, halved);
        return vget_lane_u32(halved, 0);
      }
    }
  }

  template<typename T>
  EVE_FORCEINLINE std::pair<int, bool>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(neon128_), logical<wide<T, fixed<4>>> mask)
  {
    using l_t = logical<wide<T, fixed<4>>>;

    using bits_type = typename l_t::bits_type;

    bits_type bits = mask.bits();
    bits_type elements_bit{1, 2, 4, 8};
    bits &= elements_bit;

    auto sum = sum4(bits);
    return {(sum & 7), (sum & 8)};
  }
}
