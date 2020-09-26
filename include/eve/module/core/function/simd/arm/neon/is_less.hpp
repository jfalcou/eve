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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_(EVE_SUPPORTS(neon128_),
                                                    wide<T, N, arm_64_> const &v0,
                                                    wide<T, N, arm_64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vclt_f32(v0, v1);
#if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>) return vclt_f64(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 8) return vclt_s64(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return vclt_u64(v0, v1);
#else
    else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less, v0, v1);
#endif

    else if constexpr(is_signed_int && sizeof(T) == 4) return vclt_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2) return vclt_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1) return vclt_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4) return vclt_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2) return vclt_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1) return vclt_u8(v0, v1);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_(EVE_SUPPORTS(neon128_),
                                                    wide<T, N, arm_128_> const &v0,
                                                    wide<T, N, arm_128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(std::is_same_v<T, float>) return vcltq_f32(v0, v1);
 #if defined(__aarch64__)
    else if constexpr(std::is_same_v<T, double>) return vcltq_f64(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 8) return vcltq_s64(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return vcltq_u64(v0, v1);
#else
    else if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_less, v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_less, v0, v1);
#endif
   else if constexpr(is_signed_int && sizeof(T) == 4) return vcltq_s32(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 2) return vcltq_s16(v0, v1);
    else if constexpr(is_signed_int && sizeof(T) == 1) return vcltq_s8(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 4) return vcltq_u32(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 2) return vcltq_u16(v0, v1);
    else if constexpr(is_unsigned_int && sizeof(T) == 1) return vcltq_u8(v0, v1);
  }
}

