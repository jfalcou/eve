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
  EVE_FORCEINLINE wide<T, N, ABI_> bit_select_(EVE_SUPPORTS(neon128_),
                                               wide<T, N, ABI> const &m,
                                               wide<T, N, ABI> const &v0,
                                               wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#if defined(__aarch64__)
         if constexpr(cat == category::float64x1) return vbsl_f64(vreinterpret_u64_f64(m), v0, v1);
    else if constexpr(cat == category::float64x2) return vbslq_f64(vreinterpretq_u64_f64(m), v0, v1);
#endif
    else if constexpr(cat == category::float32x2) return vbsl_f32(vreinterpret_u32_f32(m), v0, v1);
    else if constexpr(cat == category::int64x1)   return vbsl_s64(vreinterpret_u64_s64(m), v0, v1);
    else if constexpr(cat == category::int32x2)   return vbsl_s32(vreinterpret_u32_s32(m), v0, v1);
    else if constexpr(cat == category::int16x4)   return vbsl_s16(vreinterpret_u16_s16(m), v0, v1);
    else if constexpr(cat == category::int8x8)    return vbsl_s8(vreinterpret_u8_s8(m), v0, v1);
    else if constexpr(cat == category::uint64x1)  return vbsl_u64(m, v0, v1);
    else if constexpr(cat == category::uint32x2)  return vbsl_u32(m, v0, v1);
    else if constexpr(cat == category::uint16x4)  return vbsl_u16(m, v0, v1);
    else if constexpr(cat == category::uint8x8)   return vbsl_u8(m, v0, v1);
    else if constexpr(cat == category::float32x4) return vbslq_f32(vreinterpretq_u32_f32(m), v0, v1);
    else if constexpr(cat == category::int64x2)   return vbslq_s64(vreinterpretq_u64_s64(m), v0, v1);
    else if constexpr(cat == category::int32x4)   return vbslq_s32(vreinterpretq_u32_s32(m), v0, v1);
    else if constexpr(cat == category::int16x8)   return vbslq_s16(vreinterpretq_u16_s16(m), v0, v1);
    else if constexpr(cat == category::int8x16)   return vbslq_s8(vreinterpretq_u8_s8(m), v0, v1);
    else if constexpr(cat == category::uint64x2)  return vbslq_u64(m, v0, v1);
    else if constexpr(cat == category::uint32x4)  return vbslq_u32(m, v0, v1);
    else if constexpr(cat == category::uint16x8)  return vbslq_u16(m, v0, v1);
    else if constexpr(cat == category::uint8x16)  return vbslq_u8(m, v0, v1);
  }
}


// #include <eve/detail/overload.hpp>
// #include <eve/detail/abi.hpp>
// #include <eve/forward.hpp>
// #include <type_traits>

// namespace eve::detail
// {
//   template<typename T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> bit_select_(EVE_SUPPORTS(neon128_),
//                                                       wide<T, N, arm_64_> const &m,
//                                                       wide<T, N, arm_64_> const &v0,
//                                                       wide<T, N, arm_64_> const &v1) noexcept
//   {
//     using in_t = typename wide<T, N, arm_64_>::storage_type;

// // Dispatch to sub-functions
// #if defined(__aarch64__)
//     if constexpr(std::is_same_v<in_t, float64x1_t>)
//       return vbsl_f64(vreinterpret_u64_f64(m), v0, v1);
// #endif

//     if constexpr(std::is_same_v<in_t, float32x2_t>)
//       return vbsl_f32(vreinterpret_u32_f32(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int64x1_t>) return vbsl_s64(vreinterpret_u64_s64(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int32x2_t>) return vbsl_s32(vreinterpret_u32_s32(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int16x4_t>) return vbsl_s16(vreinterpret_u16_s16(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int8x8_t>) return vbsl_s8(vreinterpret_u8_s8(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, uint64x1_t>) return vbsl_u64(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint32x2_t>) return vbsl_u32(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint16x4_t>) return vbsl_u16(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint8x8_t>) return vbsl_u8(m, v0, v1);
//   }

//   template<typename T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> bit_select_(EVE_SUPPORTS(neon128_),
//                                                        wide<T, N, arm_128_> const &m,
//                                                        wide<T, N, arm_128_> const &v0,
//                                                        wide<T, N, arm_128_> const &v1) noexcept
//   {
//     using in_t = typename wide<T, N, arm_128_>::storage_type;

// // Dispatch to sub-functions
// #if defined(__aarch64__)
//     if constexpr(std::is_same_v<in_t, float64x2_t>)
//       return vbslq_f64(vreinterpretq_u64_f64(m), v0, v1);
// #endif

//     if constexpr(std::is_same_v<in_t, float32x4_t>)
//       return vbslq_f32(vreinterpretq_u32_f32(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int64x2_t>)
//       return vbslq_s64(vreinterpretq_u64_s64(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int32x4_t>)
//       return vbslq_s32(vreinterpretq_u32_s32(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int16x8_t>)
//       return vbslq_s16(vreinterpretq_u16_s16(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, int8x16_t>) return vbslq_s8(vreinterpretq_u8_s8(m), v0, v1);

//     if constexpr(std::is_same_v<in_t, uint64x2_t>) return vbslq_u64(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint32x4_t>) return vbslq_u32(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint16x8_t>) return vbslq_u16(m, v0, v1);
//     if constexpr(std::is_same_v<in_t, uint8x16_t>) return vbslq_u8(m, v0, v1);
//   }
// }
