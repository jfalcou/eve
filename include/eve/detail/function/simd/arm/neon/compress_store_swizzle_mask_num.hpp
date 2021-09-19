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

  // FIX-#965: most of this should be in reduce, except for uint8_t
  template <std::unsigned_integral T>
  EVE_FORCEINLINE auto sum8(wide<T, eve::fixed<8>> v)
  {
    if constexpr ( sizeof(T) == 1 )
    {
      using u16_4 = typename wide<T, fixed<8>>::template rebind<std::uint16_t, fixed<4>>;
      return sum4(u16_4(vpaddl_u8(v)));
    }
    else if constexpr ( current_api >= asimd && sizeof(T) == 2 ) return vaddvq_u16(v);
    else if constexpr ( sizeof(T) == 2 )
    {
      using u32_4 = typename wide<T, fixed<8>>::template rebind<std::uint32_t, fixed<4>>;
      return sum4(u32_4(vpaddlq_u16(v)));
    }
    else // aggrgated
    {
      auto [l, h] = v.slice();
      l += h;
      return sum4(l);
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

  template<typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(neon128_), logical<wide<T, fixed<8>>> mask)
  {
    // the sums we do won't fit into a char - needs to be converted to short
    using l_t = logical<wide<T, fixed<8>>>;

    using bits_type = typename l_t::bits_type;

    // See comments in the x86 version for chars
    bits_type bits = mask.bits();

    bits_type elements_bit{0x81, 0x81, 0x83, 0x83, 0x89, 0x89, 0x80, 0x80};
    bits &= elements_bit;

    int desc = sum8(bits);

    int num      = desc & 0x1f;
    int popcount = desc >> 7;
    return {num, popcount};
  }
}
