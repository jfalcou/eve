//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fms_( EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon64_> const &v0,
                                            wide<T, N, neon64_> const &v1,
                                            wide<T, N, neon64_> const &v2
                                          ) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmls_f64(v2, v1, v0);
#endif

    if constexpr(std::is_same_v<T, float>) return vmls_f32(v2, v1, v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(fms, v0, v1, v2);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmls_s32(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmls_s16(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmls_s8(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(fms, v0, v1, v2);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmls_u32(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmls_u16(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmls_u8(v2, v1, v0);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fms_ ( EVE_SUPPORTS(neon128_),
                                              wide<T, N, neon128_> const &v0,
                                              wide<T, N, neon128_> const &v1,
                                              wide<T, N, neon128_> const &v2
                                            ) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmlsq_f64(v2, v1, v0);
#endif

    if constexpr(std::is_same_v<T, float>) return vmlsq_f32(v2, v1, v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(fms, v0, v1, v2);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmlsq_s32(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmlsq_s16(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmlsq_s8(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(fms, v0, v1, v2);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmlsq_u32(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmlsq_u16(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmlsq_u8(v2, v1, v0);
  }
}

#endif
