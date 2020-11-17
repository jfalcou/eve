//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_64_> min_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, arm_64_> const &v0,
                                           wide<T, N, arm_64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

         if constexpr(std::is_same_v<T, float>)         return vmin_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)        return vmin_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)   return map(eve::min, v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 4)   return vmin_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)   return vmin_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)   return vmin_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::min, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4) return vmin_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2) return vmin_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1) return vmin_u8(v0, v1);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_128_> min_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, arm_128_> const &v0,
                                            wide<T, N, arm_128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>)               return vminq_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>)         return vminq_f64(v0, v1);
#endif
    else if constexpr(is_signed_int && sizeof(T) == 8)   return map(eve::min, v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 4)   return vminq_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2)   return vminq_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1)   return vminq_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::min, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4) return vminq_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2) return vminq_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1) return vminq_u8(v0, v1);
  }

  template<real_scalar_value T, typename N,  arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> min_( EVE_SUPPORTS(neon128_), pedantic_type const &
                                      , wide<T, N, ABI> const &a0
                                      , wide<T, N, ABI> const &a1
                                      ) noexcept
  {
    auto tmp = eve::min(a0, a1);
    if constexpr(eve::platform::supports_invalids) tmp = if_else(is_nan(a1), a0, tmp);
    return if_else(is_eqz(a0) && is_eqz(a1), bit_or(a0, a1), tmp);
  }
}
