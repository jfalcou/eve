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
#include <eve/logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE logical<T> extract_(EVE_SUPPORTS(neon128_),
                                      logical<wide<T, N, neon64_>> const &v0,
                                      std::integral_constant<I, V> const &u) noexcept
  {
    return logical<T>(extract(v0.bits(), u));
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon64_> const &v0,
                             std::integral_constant<I, V> const &) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(supports_aarch64 && std::is_same_v<T, double>) return vget_lane_f64(v0, V);
    if constexpr(std::is_same_v<T, float>) return vget_lane_f32(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 8) return vget_lane_s64(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 4) return vget_lane_s32(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 2) return vget_lane_s16(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 1) return vget_lane_s8(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vget_lane_u64(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vget_lane_u32(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vget_lane_u16(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vget_lane_u8(v0, V);
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE logical<T> extract_(EVE_SUPPORTS(neon128_),
                                      logical<wide<T, N, neon128_>> const &v0,
                                      std::integral_constant<I, V> const & u) noexcept
  {
    return logical<T>(extract(v0.bits(), u));
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon128_> const &v0,
                             std::integral_constant<I, V> const &) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(supports_aarch64 && std::is_same_v<T, double>) return vgetq_lane_f64(v0, V);
    if constexpr(std::is_same_v<T, float>) return vgetq_lane_f32(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 8) return vgetq_lane_s64(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 4) return vgetq_lane_s32(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 2) return vgetq_lane_s16(v0, V);
    if constexpr(is_signed_int && sizeof(T) == 1) return vgetq_lane_s8(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 8) return vgetq_lane_u64(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 4) return vgetq_lane_u32(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 2) return vgetq_lane_u16(v0, V);
    if constexpr(is_unsigned_int && sizeof(T) == 1) return vgetq_lane_u8(v0, V);
  }
}

