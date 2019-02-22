//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ADD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> add_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vadd_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vadd_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vadd_s64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vadd_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vadd_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vadd_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vadd_u64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vadd_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vadd_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vadd_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> add_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vaddq_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vaddq_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vaddq_s64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vaddq_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vaddq_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vaddq_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vaddq_u64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vaddq_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vaddq_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vaddq_u8(v0, v1);
  }
}

#endif
