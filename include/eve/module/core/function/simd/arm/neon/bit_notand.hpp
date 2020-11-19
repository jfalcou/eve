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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/detail/category.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> bit_notand_(EVE_SUPPORTS(neon128_),
                                                      wide<T, N, ABI> const &v0,
                                                      wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>();

    if constexpr(cat == float32x4_t>)
      return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(v1), vreinterpretq_u32_f32(v0)));
    else if constexpr( cat == category::float32x2)
      return vreinterpret_f32_u32(vbic_u32(vreinterpret_u32_f32(v1), vreinterpret_u32_f32(v0)));
#if defined(__aarch64__)
    else if constexpr( cat == category::float64x1)
      return vreinterpret_f64_u64(vbic_u64(vreinterpret_u64_f64(v1), vreinterpret_u64_f64(v0)));
    else if constexpr(cat == float64x2>)
      return vreinterpretq_f64_u64(vbicq_u64(vreinterpretq_u64_f64(v1), vreinterpretq_u64_f64(v0)));
#endif
    else if constexpr(cat == int64x1)  return vbic_s64(v1, v0);
    else if constexpr(cat == int32x2)  return vbic_s32(v1, v0);
    else if constexpr(cat == int16x4)  return vbic_s16(v1, v0);
    else if constexpr(cat == int8x8)   return vbic_s8(v0,  v1);
    else if constexpr(cat == uint64x1) return vbic_u64(v1, v0);
    else if constexpr(cat == uint32x2) return vbic_u32(v1, v0);
    else if constexpr(cat == uint16x4) return vbic_u16(v1, v0);
    else if constexpr(cat == uint8x8)  return vbic_u8(v0,  v1);
    else if constexpr(cat == int64x2)  return vbicq_s64(v1, v0);
    else if constexpr(cat == int32x4)  return vbicq_s32(v1, v0);
    else if constexpr(cat == int16x8)  return vbicq_s16(v1, v0);
    else if constexpr(cat == int8x16)  return vbicq_s8(v1, v0);
    else if constexpr(cat == uint64x2) return vbicq_u64(v1, v0);
    else if constexpr(cat == uint32x4) return vbicq_u32(v1, v0);
    else if constexpr(cat == uint16x8) return vbicq_u16(v1, v0);
    else if constexpr(cat == uint8x16) return vbicq_u8(v1, v0);
  }
}

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> bit_notand_(EVE_SUPPORTS(neon128_),
//                                                       wide<T, N, arm_64_> const &v0,
//                                                       wide<T, N, arm_64_> const &v1) noexcept
//   {
//     using in_t = typename wide<T, N, arm_64_>::storage_type;

// // Dispatch to sub-functions
//          if constexpr(std::is_same_v<in_t, float32x2_t>)
//             return vreinterpret_f32_u32(vbic_u32(vreinterpret_u32_f32(v1), vreinterpret_u32_f32(v0)));
// #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<in_t, float64x1_t>)
//             return vreinterpret_f64_u64(vbic_u64(vreinterpret_u64_f64(v1), vreinterpret_u64_f64(v0)));
// #endif
//     else if constexpr(std::is_same_v<in_t, int64x1_t>)  return vbic_s64(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int32x2_t>)  return vbic_s32(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int16x4_t>)  return vbic_s16(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int8x8_t>)   return vbic_s8(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint64x1_t>) return vbic_u64(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint32x2_t>) return vbic_u32(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint16x4_t>) return vbic_u16(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint8x8_t>)  return vbic_u8(v1, v0);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> bit_notand_(EVE_SUPPORTS(neon128_),
//                                                        wide<T, N, arm_128_> const &v0,
//                                                        wide<T, N, arm_128_> const &v1) noexcept
//   {
//     using in_t = typename wide<T, N, arm_128_>::storage_type;

// // Dispatch to sub-functions
//          if constexpr(std::is_same_v<in_t, float32x4_t>)
//             return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(v1), vreinterpretq_u32_f32(v0)));
// #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<in_t, float64x2_t>)
//             return vreinterpretq_f64_u64(vbicq_u64(vreinterpretq_u64_f64(v1), vreinterpretq_u64_f64(v0)));
// #endif
//     else if constexpr(std::is_same_v<in_t, int64x2_t>)  return vbicq_s64(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int32x4_t>)  return vbicq_s32(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int16x8_t>)  return vbicq_s16(v1, v0);
//     else if constexpr(std::is_same_v<in_t, int8x16_t>)  return vbicq_s8(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint64x2_t>) return vbicq_u64(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint32x4_t>) return vbicq_u32(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint16x8_t>) return vbicq_u16(v1, v0);
//     else if constexpr(std::is_same_v<in_t, uint8x16_t>) return vbicq_u8(v1, v0);
//   }
// }
