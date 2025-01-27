//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_equal_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(almost))
    {
      return is_less_equal.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr (cat == category::int32x4)   return vcleq_s32(a, b);
      else if constexpr (cat == category::int16x8)   return vcleq_s16(a, b);
      else if constexpr (cat == category::int8x16)   return vcleq_s8(a, b);
      else if constexpr (cat == category::uint32x4)  return vcleq_u32(a, b);
      else if constexpr (cat == category::uint16x8)  return vcleq_u16(a, b);
      else if constexpr (cat == category::uint8x16)  return vcleq_u8(a, b);
      else if constexpr (cat == category::float32x4) return vcleq_f32(a, b);
      else if constexpr (cat == category::int32x2)   return vcle_s32(a, b);
      else if constexpr (cat == category::int16x4)   return vcle_s16(a, b);
      else if constexpr (cat == category::int8x8)    return vcle_s8(a, b);
      else if constexpr (cat == category::uint32x2)  return vcle_u32(a, b);
      else if constexpr (cat == category::uint16x4)  return vcle_u16(a, b);
      else if constexpr (cat == category::uint8x8)   return vcle_u8(a, b);
      else if constexpr (cat == category::float32x2) return vcle_f32(a, b);
      else if constexpr (current_api >= asimd)
      {
        if      constexpr (cat == category::float64x1) return vcle_f64(a, b);
        else if constexpr (cat == category::int64x1)   return vcle_s64(a, b);
        else if constexpr (cat == category::uint64x1)  return vcle_u64(a, b);
        else if constexpr (cat == category::float64x2) return vcleq_f64(a, b);
        else if constexpr (cat == category::int64x2)   return vcleq_s64(a, b);
        else if constexpr (cat == category::uint64x2)  return vcleq_u64(a, b);
      }
      else return map([](auto e, auto f){ return e <= f; }, a, b);
    }
  }
}
