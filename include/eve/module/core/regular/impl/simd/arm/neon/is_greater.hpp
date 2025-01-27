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
  EVE_FORCEINLINE logical<wide<T, N>> is_greater_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(definitely))
    {
      return is_greater.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr (cat == category::int32x4)   return vcgtq_s32(a, b);
      else if constexpr (cat == category::int16x8)   return vcgtq_s16(a, b);
      else if constexpr (cat == category::int8x16)   return vcgtq_s8(a, b);
      else if constexpr (cat == category::uint32x4)  return vcgtq_u32(a, b);
      else if constexpr (cat == category::uint16x8)  return vcgtq_u16(a, b);
      else if constexpr (cat == category::uint8x16)  return vcgtq_u8(a, b);
      else if constexpr (cat == category::float32x4) return vcgtq_f32(a, b);
      else if constexpr (cat == category::int32x2)   return vcgt_s32(a, b);
      else if constexpr (cat == category::int16x4)   return vcgt_s16(a, b);
      else if constexpr (cat == category::int8x8)    return vcgt_s8(a, b);
      else if constexpr (cat == category::uint32x2)  return vcgt_u32(a, b);
      else if constexpr (cat == category::uint16x4)  return vcgt_u16(a, b);
      else if constexpr (cat == category::uint8x8)   return vcgt_u8(a, b);
      else if constexpr (cat == category::float32x2) return vcgt_f32(a, b);
      else if constexpr (current_api >= asimd)
      {
        if      constexpr (cat == category::float64x1) return vcgt_f64(a, b);
        else if constexpr (cat == category::int64x1)   return vcgt_s64(a, b);
        else if constexpr (cat == category::uint64x1)  return vcgt_u64(a, b);
        else if constexpr (cat == category::float64x2) return vcgtq_f64(a, b);
        else if constexpr (cat == category::int64x2)   return vcgtq_s64(a, b);
        else if constexpr (cat == category::uint64x2)  return vcgtq_u64(a, b);
      }
      else return map([]<typename E>(E e, E f){ return as_logical_t<E>(e > f); }, a, b);
    }
  }
}
