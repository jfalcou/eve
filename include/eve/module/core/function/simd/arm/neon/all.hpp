//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> all_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return v0;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vall_f64(v0);
#endif
    if constexpr(std::is_same_v<T, float>) return vall_f32(v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::all, v0);
    if constexpr(is_signed_int && sizeof(T) == 4) return vall_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vall_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vall_s8(v0);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> all_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return v0;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vallq_f64(v0);
#endif
    if constexpr(std::is_same_v<T, float>) return vallq_f32(v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::all, v0);
    if constexpr(is_signed_int && sizeof(T) == 4) return vallq_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vallq_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vallq_s8(v0);
  }
}

#endif
