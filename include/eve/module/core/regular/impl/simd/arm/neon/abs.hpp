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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& v) noexcept requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(saturated2))
    {
      return abs_(EVE_TARGETS(cpu_), opts, v);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr( match(cat, category::unsigned_)  ) return v;
      else if constexpr( match(cat, category::size64_)    ) return map(eve::abs, v);
      else if constexpr( cat == category::float32x4       ) return vabsq_f32(v);
      else if constexpr( cat == category::int32x4         ) return vabsq_s32(v);
      else if constexpr( cat == category::int16x8         ) return vabsq_s16(v);
      else if constexpr( cat == category::int8x16         ) return vabsq_s8(v);
      else if constexpr( cat == category::float32x2       ) return vabs_f32(v);
      else if constexpr( cat == category::int32x2         ) return vabs_s32(v);
      else if constexpr( cat == category::int16x4         ) return vabs_s16(v);
      else if constexpr( cat == category::int8x8          ) return vabs_s8(v);
      else if constexpr( current_api >= asimd             )
      {
        if      constexpr( cat == category::float64x2 ) return vabsq_f64(v);
        else if constexpr( cat == category::float64x1 ) return vabs_f64(v);
        else    EVE_UNREACHABLE();
      }
      else      EVE_UNREACHABLE();
    }
  }
}
