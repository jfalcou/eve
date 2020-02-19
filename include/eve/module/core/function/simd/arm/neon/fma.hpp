//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fma_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmla_f64(v2, v1, v0);
#endif

    if constexpr(std::is_same_v<T, float>) return vmla_f32(v2, v1, v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(fma, v0, v1, v2);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmla_s32(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmla_s16(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmla_s8(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(fma, v0, v1, v2);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmla_u32(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmla_u16(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmla_u8(v2, v1, v0);
  }

  template<typename D, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fma_(EVE_SUPPORTS(neon128_),
                                           D const &, 
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    return fma(v0, v1, v2); 
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fma_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmlaq_f64(v2, v1, v0);
#endif

    if constexpr(std::is_same_v<T, float>) return vmlaq_f32(v2, v1, v0);

    if constexpr(is_signed_int && sizeof(T) == 8) return map(fma, v0, v1, v2);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmlaq_s32(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmlaq_s16(v2, v1, v0);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmlaq_s8(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(fma, v0, v1, v2);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmlaq_u32(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmlaq_u16(v2, v1, v0);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmlaq_u8(v2, v1, v0);
  }

  template<typename D, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fma_(EVE_SUPPORTS(neon128_),
                                            D const &, 
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    return fma(v0, v1, v2); 
  }

  
}

#endif
