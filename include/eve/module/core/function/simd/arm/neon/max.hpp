//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MAX_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MAX_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> max_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmax_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vmax_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::max, v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmax_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmax_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmax_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::max, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmax_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmax_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmax_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> max_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmaxq_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vmaxq_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::max, v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmaxq_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmaxq_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmaxq_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::max, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmaxq_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmaxq_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmaxq_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> max_(EVE_SUPPORTS(neon128_),
                                           pedantic_type const &,
                                           wide<T, N, neon64_> const &a0,
                                           wide<T, N, neon64_> const &a1) noexcept
  {
#if !defined(EVE_SIMD_NO_NANS)
    auto tmp = if_else(is_nan(a1), a0, eve::max(a0, a1));
#else
    auto tmp = eve::max(a0, a1);
#endif
    return if_else(is_eqz(a0) && is_eqz(a1), bit_xor(a0, a1), tmp); 
  }
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> max_(EVE_SUPPORTS(neon128_),
                                            pedantic_type const &,
                                            wide<T, N, neon128_> const &a0,
                                            wide<T, N, neon128_> const &a1) noexcept
  {
#if !defined(EVE_SIMD_NO_NANS)
    auto tmp = if_else(is_nan(a1), a0, eve::max(a0, a1));
#else
    auto tmp = eve::max(a0, a1);
#endif
    return if_else(is_eqz(a0) && is_eqz(a1), bit_xor(a0, a1), tmp); 
  }

}

#endif
