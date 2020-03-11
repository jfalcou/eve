//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> abs_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return v0;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vabs_f64(v0);
#endif
    if constexpr(std::is_same_v<T, float>) return vabs_f32(v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::abs, v0);
    if constexpr(is_signed_int && sizeof(T) == 4) return vabs_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vabs_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vabs_s8(v0);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> abs_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(is_unsigned_int) return v0;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vabsq_f64(v0);
#endif
    if constexpr(std::is_same_v<T, float>) return vabsq_f32(v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::abs, v0);
    if constexpr(is_signed_int && sizeof(T) == 4) return vabsq_s32(v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vabsq_s16(v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vabsq_s8(v0);
  }
}

#endif
