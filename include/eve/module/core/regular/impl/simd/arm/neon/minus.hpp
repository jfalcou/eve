//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> minus_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v) noexcept
  requires( arm_abi<abi_t<T, N>> && !Opts::contains(mod))
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if constexpr (O::contains(saturated) && std::integral<T>)
    {
      return minus.behavior(cpu_{}, opts, v);
    }
    else
    {
      if constexpr( cat == category::float32x4 )      return vnegq_f32(v);
      else if constexpr( cat == category::int32x4 )   return vnegq_s32(v);
      else if constexpr( cat == category::int16x8 )   return vnegq_s16(v);
      else if constexpr( cat == category::int8x16 )   return vnegq_s8(v);
      else if constexpr( cat == category::float32x2 ) return vneg_f32(v);
      else if constexpr( cat == category::int32x2 )   return vneg_s32(v);
      else if constexpr( cat == category::int16x4 )   return vneg_s16(v);
      else if constexpr( cat == category::int8x8 )    return vneg_s8(v);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x2 )      return vnegq_f64(v);
        else if constexpr( cat == category::float64x1 ) return vneg_f64(v);
        else return minus.behavior(cpu_{}, opts, v);
      }
      else
      {
        return minus.behavior(cpu_{}, opts, v);
      }
    }
  }
}
