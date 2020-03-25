//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> mul_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vmul_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)
      return vmul_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)
      return map(mul, v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 4)
      return vmul_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)
      return vmul_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)
      return vmul_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8)
      return map(mul, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4)
      return vmul_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2)
      return vmul_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1)
      return vmul_u8(v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_),
                            U const &                  v0,
                            wide<T, N, neon64_> const &v1) noexcept Requires(wide<T, N, neon64_>,
                                                                             Vectorizable<U>)
  {
    return mul(v1, v0);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_),
                            wide<T, N, neon64_> const &v0,
                            U const &v1) noexcept Requires(wide<T, N, neon64_>, Vectorizable<U>)
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vmul_n_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)
      return vmul_n_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)
      return map(mul, v0, static_cast<T>(v1));
    else if constexpr(is_signed_int && sizeof(T) == 4)
      return vmul_n_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)
      return vmul_n_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)
      return vmul_s8(v0, wide<T, N, neon64_>(v1));
    else if constexpr(is_unsigned_int && sizeof(T) == 8)
      return map(mul, v0, static_cast<T>(v1));
    else if constexpr(is_unsigned_int && sizeof(T) == 4)
      return vmul_n_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2)
      return vmul_n_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1)
      return vmul_u8(v0, wide<T, N, neon64_>(v1));
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> mul_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vmulq_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)
      return vmulq_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)
      return map(mul, v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 4)
      return vmulq_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)
      return vmulq_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)
      return vmulq_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8)
      return map(mul, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4)
      return vmulq_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2)
      return vmulq_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1)
      return vmulq_u8(v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_),
                            U const &                   v0,
                            wide<T, N, neon128_> const &v1) noexcept Requires(wide<T, N, neon128_>,
                                                                              Vectorizable<U>)
  {
    return mul(v1, v0);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_),
                            wide<T, N, neon128_> const &v0,
                            U const &v1) noexcept Requires(wide<T, N, neon128_>, Vectorizable<U>)
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vmulq_n_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)
      return vmulq_n_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)
      return map(mul, v0, static_cast<T>(v1));
    else if constexpr(is_signed_int && sizeof(T) == 4)
      return vmulq_n_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)
      return vmulq_n_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)
      return vmulq_s8(v0, wide<T, N, neon128_>(v1));
    else if constexpr(is_unsigned_int && sizeof(T) == 8)
      return map(mul, v0, static_cast<T>(v1));
    else if constexpr(is_unsigned_int && sizeof(T) == 4)
      return vmulq_n_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2)
      return vmulq_n_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1)
      return vmulq_u8(v0, wide<T, N, neon128_>(v1));
  }
}

#endif
