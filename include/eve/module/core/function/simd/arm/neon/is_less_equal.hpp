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
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_equal_(EVE_SUPPORTS(neon128_),
                                                          wide<T, N, ABI> const &v0,
                                                          wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

    if constexpr( cat == category::int32x4  ) return vcleq_s32(v0, v1);
    else  if constexpr( cat == category::int16x8  ) return vcleq_s16(v0, v1);
    else  if constexpr( cat == category::int8x16  ) return vcleq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x4 ) return vcleq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x8 ) return vcleq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x16 ) return vcleq_u8(v0, v1);
    else  if constexpr( cat == category::float32x4) return vcleq_f32(v0, v1);
    else  if constexpr( cat == category::int32x2  ) return vcle_s32(v0, v1);
    else  if constexpr( cat == category::int16x4  ) return vcle_s16(v0, v1);
    else  if constexpr( cat == category::int8x8   ) return vcle_s8(v0, v1);
    else  if constexpr( cat == category::uint32x2 ) return vcle_u32(v0, v1);
    else  if constexpr( cat == category::uint16x4 ) return vcle_u16(v0, v1);
    else  if constexpr( cat == category::uint8x8  ) return vcle_u8(v0, v1);
    else  if constexpr( cat == category::float32x2) return vcle_f32(v0, v1);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vcle_f64(v0, v1);
    else  if constexpr( cat == category::int64x1)   return vcle_s64(v0, v1);
    else  if constexpr( cat == category::uint64x1)  return vcle_u64(v0, v1);
    else  if constexpr( cat == category::float64x2) return vcleq_f64(v0, v1);
    else  if constexpr( cat == category::int64x2)   return vcleq_s64(v0, v1);
    else  if constexpr( cat == category::uint64x2)  return vcleq_u64(v0, v1);
#else
    else  if constexpr( sizeof(T) == 8 )            return map(is_less_equal, v0, v1);
#endif
  }
}

// #include <eve/detail/overload.hpp>
// #include <eve/detail/abi.hpp>
// #include <eve/forward.hpp>
// #include <eve/concept/value.hpp>

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_equal_(EVE_SUPPORTS(neon128_),
//                                                           wide<T, N, arm_64_> const &v0,
//                                                           wide<T, N, arm_64_> const &v1) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//     if constexpr(std::is_same_v<T, float>) return vcle_f32(v0, v1);
// #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<T, double>) return vcle_f64(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 8) return vcle_s64(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return vcle_u64(v0, v1);
// #else
//     else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
// #endif

//     else if constexpr(is_signed_int && sizeof(T) == 4) return vcle_s32(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 2) return vcle_s16(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 1) return vcle_s8(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 4) return vcle_u32(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 2) return vcle_u16(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 1) return vcle_u8(v0, v1);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_equal_(EVE_SUPPORTS(neon128_),
//                                                           wide<T, N, arm_128_> const &v0,
//                                                           wide<T, N, arm_128_> const &v1) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//    if constexpr(std::is_same_v<T, float>) return vcleq_f32(v0, v1);
//  #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<T, double>) return vcleq_f64(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 8) return vcleq_s64(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return vcleq_u64(v0, v1);
// #else
//     else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
// #endif
//     else if constexpr(is_signed_int && sizeof(T) == 4) return vcleq_s32(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 2) return vcleq_s16(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 1) return vcleq_s8(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 4) return vcleq_u32(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 2) return vcleq_u16(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 1) return vcleq_u8(v0, v1);
//   }
// }
