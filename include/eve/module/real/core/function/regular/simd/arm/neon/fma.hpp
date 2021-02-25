//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fma_(EVE_SUPPORTS(neon128_),
                                       wide<T, N, ABI> const &v0,
                                       wide<T, N, ABI> const &v1,
                                       wide<T, N, ABI> const &v2) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr(  cat == category::float32x2) return  vfma_f32(v2, v1, v0);
    else if constexpr(  cat == category::float32x4) return vfmaq_f32(v2, v1, v0);
    else  if constexpr( cat == category::int32x4  ) return vmlaq_s32(v2, v1, v0);
    else  if constexpr( cat == category::int16x8  ) return vmlaq_s16(v2, v1, v0);
    else  if constexpr( cat == category::int8x16  ) return  vmlaq_s8(v2, v1, v0);
    else  if constexpr( cat == category::int32x2  ) return  vmla_s32(v2, v1, v0);
    else  if constexpr( cat == category::int16x4  ) return  vmla_s16(v2, v1, v0);
    else  if constexpr( cat == category::int8x8   ) return   vmla_s8(v2, v1, v0);
    else  if constexpr( cat == category::uint32x4 ) return vmlaq_u32(v2, v1, v0);
    else  if constexpr( cat == category::uint16x8 ) return vmlaq_u16(v2, v1, v0);
    else  if constexpr( cat == category::uint8x16 ) return  vmlaq_u8(v2, v1, v0);
    else  if constexpr( cat == category::uint32x2 ) return  vmla_u32(v2, v1, v0);
    else  if constexpr( cat == category::uint16x4 ) return  vmla_u16(v2, v1, v0);
    else  if constexpr( cat == category::uint8x8  ) return   vmla_u8(v2, v1, v0);
    else if constexpr( current_api >= asimd )
    {
            if constexpr(  cat == category::float64x1)  return  vfma_f64(v2, v1, v0);
      else  if constexpr(  cat == category::float64x2)  return vfmaq_f64(v2, v1, v0);
      else                                              return  map(fma, v0, v1, v2);
    }
    else  if constexpr( sizeof(T) == 8 )            return  map(fma, v0, v1, v2);
  }
}
