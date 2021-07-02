//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N> const &v0
                                      , as<U> const &tgt) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto catin = categorize<wide<T, N>>();
    constexpr auto catou = categorize<wide<U, N>>();

    // Idempotent call
    if constexpr( std::is_same_v<T, U> ) return v0;

    if constexpr ( std::signed_integral<T> && std::unsigned_integral<U> )
    {
      using s_u = std::make_signed_t<U>;
      auto s_res = convert(v0, eve::as<s_u>{});
      return bit_cast(s_res, eve::as<wide<U, N>>{});
    }
    else if constexpr ( std::unsigned_integral<T> && std::signed_integral<U> )
    {
      using u_u = std::make_unsigned_t<U>;
      auto u_res = convert(v0, eve::as<u_u>{});
      return bit_cast(u_res, eve::as<wide<U, N>>{});
    }

    //==============================================================================================
    // double -> ?
    if constexpr( catin == category::float64x1  && current_api >= asimd )
    {
           if constexpr( catou == category::int64x1  ) return vcvt_s64_f64(v0);
      else if constexpr( catou == category::uint64x1 ) return vcvt_u64_f64(v0);
      else                                             return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::float64x2  && current_api >= asimd )
    {
           if constexpr( catou == category::int64x2  ) return vcvtq_s64_f64(v0);
      else if constexpr( catou == category::uint64x2 ) return vcvtq_u64_f64(v0);
      else if constexpr( catou == category::int32x2  ) return vmovn_s64(vcvtq_s64_f64(v0));
      else if constexpr( catou == category::uint32x2 ) return vmovn_u64(vcvtq_u64_f64(v0));
      else                                             return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else
    //==============================================================================================
    // float -> ?
    if constexpr( catin == category::float32x2 )
    {
           if constexpr( catou == category::int32x2  )      return vcvt_s32_f32(v0);
      else if constexpr( catou == category::uint32x2 )      return vcvt_u32_f32(v0);
      else if constexpr( catou == category::int64x2  )      return vmovl_s32(vcvt_s32_f32(v0));
      else if constexpr( catou == category::uint64x2 )      return vmovl_u32(vcvt_u32_f32(v0));
      else                                                  return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::float32x4 )
    {
           if constexpr( catou == category::int32x4  )      return vcvtq_s32_f32(v0);
      else if constexpr( catou == category::uint32x4 )      return vcvtq_u32_f32(v0);
      else if constexpr( catou == category::int16x4  )      return vmovn_s32(vcvtq_s32_f32(v0));
      else if constexpr( catou == category::uint16x4 )      return vmovn_u32(vcvtq_u32_f32(v0));
      else                                                  return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int64 -> ?
    else if constexpr( catin == category::int64x1 )
    {
      if constexpr( catou == category::float64x1 && current_api >= asimd) return vcvt_f64_s64(v0);
      else                                                                return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::int64x2 )
    {
           if constexpr( catou == category::float64x2  && current_api >= asimd)     return vcvtq_f64_s64(v0);
      else if constexpr( catou == category::float32x2 )                             return vcvt_f32_s32(vmovn_s64(v0));
      else if constexpr( catou == category::int32x2   )                             return vmovn_s64(v0);
      else                                                                          return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint64 -> ?
    else if constexpr( catin == category::uint64x1 )
    {
      if constexpr( catou == category::float64x1 && current_api >= asimd ) return vcvt_f64_u64(v0);
      else                                                                 return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::uint64x2 )
    {
           if constexpr( catou == category::float64x2 && current_api >= asimd ) return vcvtq_f64_u64(v0);
      else if constexpr( catou == category::float32x2 )                         return vcvt_f32_u32(vmovn_u64(v0));
      else if constexpr( catou == category::uint32x2 )                          return vmovn_u64(v0);
      else                                                                      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int32 -> ?
    else if constexpr( catin == category::int32x2 )
    {
           if constexpr( catou == category::float32x2 )        return vcvt_f32_s32(v0);
      else if constexpr( catou == category::int64x2 )          return vmovl_s32(v0);
      else                                                     return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::int32x4 )
    {
           if constexpr( catou == category::float32x4 )        return vcvtq_f32_s32(v0);
      else if constexpr( catou == category::int16x4 )          return vmovn_s32(v0);
      else                                                     return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint32 -> ?
    else if constexpr( catin == category::uint32x2 )
    {
           if constexpr( catou == category::float32x2 )        return vcvt_f32_u32(v0);
      else if constexpr( catou == category::uint64x2 )         return vmovl_u32(v0);
      else                                                     return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr( catin == category::uint32x4 )
    {
           if constexpr( catou == category::float32x4 )        return vcvtq_f32_u32(v0);
      else if constexpr( catou == category::uint16x4 )         return vmovn_u32(v0);
      else                                                     return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // int16 -> ?
    else if constexpr( catin == category::int16x4 )
    {
           if constexpr( catou == category::int32x4 )        return vmovl_s16(v0);
      else if constexpr( catou == category::float32x4 )      return vcvtq_f32_s32(vmovl_s16(v0));
      else                                                   return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr ( catin == category::int16x8 )
    {
      if constexpr ( catou == category::int8x8 )   return vmovn_s16(v0);
      else                                         return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint16 -> ?
    else if constexpr( catin == category::uint16x4 )
    {
           if constexpr( catou == category::float32x4 )  return vcvtq_f32_u32(vmovl_u16(v0));
      else if constexpr( catou == category::uint32x4 )   return vmovl_u16(v0);
      else if constexpr( catou == category::int16x4 )    return vreinterpret_s16_u16(v0);
      else                                               return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else if constexpr ( catin == category::uint16x8 )
    {
      if constexpr ( catou == category::uint8x8 ) return vmovn_u16(v0);
      else                                        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }

    //==============================================================================================
    // int8 -> ?
    else if constexpr( catin == category::int8x8 )
    {
           if constexpr( catou == category::int16x8 ) return vmovl_s8(v0);
      else                                            return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // uint8 -> ?
    else if constexpr( catin == category::uint8x8 )
    {
           if constexpr( catou == category::uint16x8 )  return vmovl_u8(v0);
      else if constexpr( catou == category::int8x8 )    return vreinterpret_s8_u8(v0);
      else                                              return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    //==============================================================================================
    // other -> ?
    else                                                     return convert_(EVE_RETARGET(simd_), v0, tgt);
   }
}
