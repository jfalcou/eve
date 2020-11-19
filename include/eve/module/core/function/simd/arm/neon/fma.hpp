//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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

         if constexpr(  cat == category::float32x2) return vfma_f32(v2, v1, v0);
    else if constexpr(  cat == category::float32x4) return vfmaq_f32(v2, v1, v0);
#if defined(__aarch64__)
    else if constexpr(  cat == category::float64x1) return vfma_f64(v2, v1, v0);
    else if constexpr(  cat == category::float64x2) return vfmaq_f64(v2, v1, v0);
#endif
    else  if constexpr( cat && category::size64_  ) return map(fma, v0, v1, v2);
    else  if constexpr( cat == category::int32x4  ) return vmlaq_s32(v2, v1, v0);
    else  if constexpr( cat == category::int16x8  ) return vmlaq_s16(v2, v1, v0);
    else  if constexpr( cat == category::int8x16  ) return vmlaq_s8(v2, v1, v0);
    else  if constexpr( cat == category::int32x2  ) return vmla_s32(v2, v1, v0);
    else  if constexpr( cat == category::int16x4  ) return vmla_s16(v2, v1, v0);
    else  if constexpr( cat == category::int8x8   ) return vmla_s8(v2, v1, v0);
    else  if constexpr( cat == category::int32x4  ) return vmlaq_u32(v2, v1, v0);
    else  if constexpr( cat == category::int16x8  ) return vmlaq_u16(v2, v1, v0);
    else  if constexpr( cat == category::int8x16  ) return vmlaq_u8(v2, v1, v0);
    else  if constexpr( cat == category::int32x2  ) return vmla_u32(v2, v1, v0);
    else  if constexpr( cat == category::int16x4  ) return vmla_u16(v2, v1, v0);
    else  if constexpr( cat == category::int8x8   ) return vmla_u8(v2, v1, v0);
  }

  template<decorator D, real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fma_(EVE_SUPPORTS(neon128_),
                                       D const &,
                                       wide<T, N, ABI> const &v0,
                                       wide<T, N, ABI> const &v1,
                                       wide<T, N, ABI> const &v2) noexcept
  {
    return fma(v0, v1, v2);
  }


}

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> fma_(EVE_SUPPORTS(neon128_),
//                                            wide<T, N, arm_64_> const &v0,
//                                            wide<T, N, arm_64_> const &v1,
//                                            wide<T, N, arm_64_> const &v2) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//     if constexpr( std::is_same_v<T, float> )
//       return vfma_f32(v2, v1, v0);
// #if defined(__aarch64__)
//     else if constexpr( std::is_same_v<T, double> )
//       return vfma_f64(v2, v1, v0);
// #endif

//     else if constexpr( is_signed_int && sizeof(T) == 8 )
//       return map(fma, v0, v1, v2);
//     else if constexpr( is_signed_int && sizeof(T) == 4 )
//       return vmla_s32(v2, v1, v0);
//     else if constexpr( is_signed_int && sizeof(T) == 2 )
//       return vmla_s16(v2, v1, v0);
//     else if constexpr( is_signed_int && sizeof(T) == 1 )
//       return vmla_s8(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 8 )
//       return map(fma, v0, v1, v2);
//     else if constexpr( is_unsigned_int && sizeof(T) == 4 )
//       return vmla_u32(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 2 )
//       return vmla_u16(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 1 )
//       return vmla_u8(v2, v1, v0);
//   }

//   template<decorator D, real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> fma_(EVE_SUPPORTS(neon128_),
//                                            D const &,
//                                            wide<T, N, arm_64_> const &v0,
//                                            wide<T, N, arm_64_> const &v1,
//                                            wide<T, N, arm_64_> const &v2) noexcept
//   {
//     return fma(v0, v1, v2);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> fma_(EVE_SUPPORTS(neon128_),
//                                             wide<T, N, arm_128_> const &v0,
//                                             wide<T, N, arm_128_> const &v1,
//                                             wide<T, N, arm_128_> const &v2) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//     if constexpr( std::is_same_v<T, float> )
//       return vfmaq_f32(v2, v1, v0);
// #if defined(__aarch64__)
//     else if constexpr( std::is_same_v<T, double> )
//       return vfmaq_f64(v2, v1, v0);
// #endif
//     else if constexpr( is_signed_int && sizeof(T) == 8 )
//       return map(fma, v0, v1, v2);
//     else if constexpr( is_signed_int && sizeof(T) == 4 )
//       return vmlaq_s32(v2, v1, v0);
//     else if constexpr( is_signed_int && sizeof(T) == 2 )
//       return vmlaq_s16(v2, v1, v0);
//     else if constexpr( is_signed_int && sizeof(T) == 1 )
//       return vmlaq_s8(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 8 )
//       return map(fma, v0, v1, v2);
//     else if constexpr( is_unsigned_int && sizeof(T) == 4 )
//       return vmlaq_u32(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 2 )
//       return vmlaq_u16(v2, v1, v0);
//     else if constexpr( is_unsigned_int && sizeof(T) == 1 )
//       return vmlaq_u8(v2, v1, v0);
//   }

//   template<decorator D, real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> fma_(EVE_SUPPORTS(neon128_),
//                                             D const &,
//                                             wide<T, N, arm_128_> const &v0,
//                                             wide<T, N, arm_128_> const &v1,
//                                             wide<T, N, arm_128_> const &v2) noexcept
//   {
//     return fma(v0, v1, v2);
//   }
// }
