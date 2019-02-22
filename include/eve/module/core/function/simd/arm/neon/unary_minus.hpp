//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_UNARY_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_UNARY_MINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/sub.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> unary_minus_(EVE_SUPPORTS(neon128_),
                                                   wide<T, N, neon64_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return Zero(as(v0)) - v0;
    if constexpr(std::is_same_v<T, float>) return vneg_f32(v0);

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vneg_f64(v0);
#endif

#if !defined(__aarch64__)
    if constexpr(is_signed_int && sizeof(T) == 8) return Zero(as(v0)) - v0;
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return vneg_s64(v0);
#endif

    if constexpr(is_signed_int && sizeof(T) == 4) return vneg_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vneg_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vneg_s8(v0);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> unary_minus_(EVE_SUPPORTS(neon128_),
                                                    wide<T, N, neon128_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return Zero(as(v0)) - v0;
    if constexpr(std::is_same_v<T, float>) return vnegq_f32(v0);

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vnegq_f64(v0);
#endif

#if !defined(__aarch64__)
    if constexpr(is_signed_int && sizeof(T) == 8) return Zero(as(v0)) - v0;
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return vnegq_s64(v0);
#endif

    if constexpr(is_signed_int && sizeof(T) == 4) return vnegq_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vnegq_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vnegq_s8(v0);
  }
}

#endif
