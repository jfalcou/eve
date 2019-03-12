//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_LESS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_LESS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<logical<T>, N> is_less_equal_(EVE_SUPPORTS(neon128_),
                                                  wide<T, N, neon64_> const &v0,
                                                  wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vcle_f64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vcle_s64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vcle_u64(v0, v1);
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
#endif

    if constexpr(std::is_same_v<T, float>) return vcle_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vcle_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vcle_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vcle_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vcle_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vcle_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vcle_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<logical<T>, N> is_less_equal_(EVE_SUPPORTS(neon128_),
                                                  wide<T, N, neon128_> const &v0,
                                                  wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vcleq_f64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vcleq_s64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vcleq_u64(v0, v1);
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less_equal, v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vcleq_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vcleq_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vcleq_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vcleq_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vcleq_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vcleq_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vcleq_u8(v0, v1);
  }
}

#endif
