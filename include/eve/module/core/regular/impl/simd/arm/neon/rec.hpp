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
#include <eve/module/core/decorator/raw.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  rec_(EVE_REQUIRES(neon128_), O const&, wide<T, N> v) noexcept
  requires (arm_abi<abi_t<T, N>>)
  {
    if constexpr(O::contains(raw2))
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if      constexpr( cat == category::float32x2 ) return vrecpe_f32(v);
      else if constexpr( cat == category::float32x4 ) return vrecpeq_f32(v);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 ) return vrecpe_f64(v);
        else if constexpr( cat == category::float64x2 ) return vrecpeq_f64(v);
      }
      else
        return T {1} / v;
    }
    else
      return T {1} / v;
  }
}
