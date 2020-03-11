//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_greater_equal_(EVE_SUPPORTS(neon128_),
                                                             wide<T, N, neon64_> const &v0,
                                                             wide<T, N, neon64_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vcge_f64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vcge_s64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vcge_u64(v0, v1);
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
#endif

    if constexpr(std::is_same_v<T, float>) return vcge_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vcge_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vcge_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vcge_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vcge_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vcge_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vcge_u8(v0, v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T, N>>
                  is_greater_equal_(EVE_SUPPORTS(neon128_),
                                    wide<T, N, neon128_> const &v0,
                                    wide<T, N, neon128_> const &v1) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) return vcgeq_f64(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 8) return vcgeq_s64(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vcgeq_u64(v0, v1);
#else
    if constexpr(is_signed_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return map(eve::is_greater_equal, v0, v1);
#endif
    if constexpr(std::is_same_v<T, float>) return vcgeq_f32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 4) return vcgeq_s32(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 2) return vcgeq_s16(v0, v1);
    if constexpr(is_signed_int && sizeof(T) == 1) return vcgeq_s8(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vcgeq_u32(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vcgeq_u16(v0, v1);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vcgeq_u8(v0, v1);
  }
}

#endif
