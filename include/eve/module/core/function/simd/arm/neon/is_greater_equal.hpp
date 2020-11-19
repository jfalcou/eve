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
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_greater_equal_(EVE_SUPPORTS(neon128_),
                                                     wide<T, N, ABI> const &v0,
                                                     wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

          if constexpr( cat == category::int32x4  ) return vcgeq_s32(v0, v1);
    else  if constexpr( cat == category::int16x8  ) return vcgeq_s16(v0, v1);
    else  if constexpr( cat == category::int8x16  ) return vcgeq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x4 ) return vcgeq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x8 ) return vcgeq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x16 ) return vcgeq_u8(v0, v1);
    else  if constexpr( cat == category::float32x4) return vcgeq_f32(v0, v1);
    else  if constexpr( cat == category::int32x2  ) return vcge_s32(v0, v1);
    else  if constexpr( cat == category::int16x4  ) return vcge_s16(v0, v1);
    else  if constexpr( cat == category::int8x8   ) return vcge_s8(v0, v1);
    else  if constexpr( cat == category::uint32x2 ) return vcge_u32(v0, v1);
    else  if constexpr( cat == category::uint16x4 ) return vcge_u16(v0, v1);
    else  if constexpr( cat == category::uint8x8  ) return vcge_u8(v0, v1);
    else  if constexpr( cat == category::float32x2) return vcge_f32(v0, v1);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vcge_f64(v0, v1);
    else  if constexpr( cat == category::int64x1)   return vcge_s64(v0, v1);
    else  if constexpr( cat == category::uint64x1)  return vcge_u64(v0, v1);
    else  if constexpr( cat == category::float64x2) return vcgeq_f64(v0, v1);
    else  if constexpr( cat == category::int64x2)   return vcgeq_s64(v0, v1);
    else  if constexpr( cat == category::uint64x2)  return vcgeq_u64(v0, v1);
#else
    else  if constexpr( sizeof(T) == 8 )            return map(is_greater_equal, v0, v1);
#endif
  }
}
// #include <eve/detail/overload.hpp>
// #include <eve/detail/abi.hpp>
// #include <eve/traits/as_logical.hpp>
// #include <eve/forward.hpp>
// #include <eve/concept/value.hpp>

// namespace eve::detail
// {
//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE as_logical_t<wide<T, N>> is_greater_equal_(EVE_SUPPORTS(neon128_),
//                                                              wide<T, N, arm_64_> const &v0,
//                                                              wide<T, N, arm_64_> const &v1) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//     if constexpr(std::is_same_v<T, float>) return vcge_f32(v0, v1);
// #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<T, double>) return vcge_f64(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 8) return vcge_s64(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return vcge_u64(v0, v1);
// #else
//     else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
// #endif

//     else if constexpr(is_signed_int && sizeof(T) == 4) return vcge_s32(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 2) return vcge_s16(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 1) return vcge_s8(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 4) return vcge_u32(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 2) return vcge_u16(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 1) return vcge_u8(v0, v1);
//   }

//   template<real_scalar_value T, typename N>
//   EVE_FORCEINLINE as_logical_t<wide<T, N>>
//                   is_greater_equal_(EVE_SUPPORTS(neon128_),
//                                     wide<T, N, arm_128_> const &v0,
//                                     wide<T, N, arm_128_> const &v1) noexcept
//   {
//     constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
//     constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

//     if constexpr(std::is_same_v<T, float>) return vcgeq_f32(v0, v1);
// #if defined(__aarch64__)
//     else if constexpr(std::is_same_v<T, double>) return vcgeq_f64(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 8) return vcgeq_s64(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return vcgeq_u64(v0, v1);
// #else
//     else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
// #endif
//     else if constexpr(is_signed_int && sizeof(T) == 4) return vcgeq_s32(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 2) return vcgeq_s16(v0, v1);
//     else if constexpr(is_signed_int && sizeof(T) == 1) return vcgeq_s8(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 4) return vcgeq_u32(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 2) return vcgeq_u16(v0, v1);
//     else if constexpr(is_unsigned_int && sizeof(T) == 1) return vcgeq_u8(v0, v1);
//   }
// }
