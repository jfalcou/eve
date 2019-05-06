//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> min_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vmin_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vmin_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vmin_s64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vmin_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vmin_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vmin_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vmin_u64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vmin_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vmin_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vmin_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> min_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vminq_f64(v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vminq_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vminq_s64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vminq_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vminq_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vminq_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vminq_u64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vminq_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vminq_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vminq_u8(v0, v1);
  }
  
  
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> min_(EVE_SUPPORTS(neon128_),
                                           pedantic_type const &, 
                                           wide<T, N, neon64_> const &a0,
                                           wide<T, N, neon64_> const &a1) noexcept
  {
#if !defined(BOOST_SIMD_NO_NANS)
    return if_else(is_nan(a1), a0, eve::min(a0, a1));
#else
    return eve::min(a0, a1); 
#endif
    
  }
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> min_(EVE_SUPPORTS(neon128_),
                                           pedantic_type const &, 
                                           wide<T, N, neon128_> const &a0,
                                           wide<T, N, neon128_> const &a1) noexcept
  {
#if !defined(BOOST_SIMD_NO_NANS)
    return if_else(is_nan(a1), a0, eve::min(a0, a1));
#else
    return eve::min(a0, a1); 
#endif
    
  }
  
}

#endif
