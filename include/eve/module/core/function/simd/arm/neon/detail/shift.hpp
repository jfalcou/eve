//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DETAIL_SHIFT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DETAIL_SHIFT_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto neon_shifter(wide<T, N, neon64_> const &v0,
                                    wide<I, N, neon64_> const &v1) noexcept
  {
    using t_t                      = wide<T, N, neon64_>;
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    using i_t = wide<as_integer_t<T, signed>, N>;
    auto s1   = bitwise_cast(v1,as_<i_t>()).storage();

    if constexpr(is_signed_int && sizeof(T) == 8) return t_t(vshl_s64(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 4) return t_t(vshl_s32(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 2) return t_t(vshl_s16(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 1) return t_t(vshl_s8(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 8) return t_t(vshl_u64(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 4) return t_t(vshl_u32(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 2) return t_t(vshl_u16(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 1) return t_t(vshl_u8(v0, s1));
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto neon_shifter(wide<T, N, neon128_> const &v0,
                                    wide<I, N, neon128_> const &v1) noexcept
  {
    using t_t                      = wide<T, N, neon128_>;
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    using i_t = wide<as_integer_t<T, signed>, N>;
    auto s1   = bitwise_cast(v1,as_<i_t>()).storage();

    if constexpr(is_signed_int && sizeof(T) == 8) return t_t(vshlq_s64(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 4) return t_t(vshlq_s32(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 2) return t_t(vshlq_s16(v0, s1));
    if constexpr(is_signed_int && sizeof(T) == 1) return t_t(vshlq_s8(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 8) return t_t(vshlq_u64(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 4) return t_t(vshlq_u32(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 2) return t_t(vshlq_u16(v0, s1));
    if constexpr(is_unsigned_int && sizeof(T) == 1) return t_t(vshlq_u8(v0, s1));
  }
}

#endif
