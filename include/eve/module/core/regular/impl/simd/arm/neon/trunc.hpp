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

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> trunc_(EVE_SUPPORTS(neon128_),
                                    O          const& o,
                                    wide<T, N> const& v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if  constexpr(!O::contains(tolerance))
    {
      constexpr auto cat = categorize<wide<T, N>>();
      
      if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 ) return vrnd_f64(v);
        else if constexpr( cat == category::float64x2 ) return vrndq_f64(v);
        else if constexpr( cat == category::float32x2 ) return vrnd_f32(v);
        else if constexpr( cat == category::float32x4 ) return vrndq_f32(v);
      }
      else return map(trunc, v);
    }
    else
      return trunc_(EVE_TARGETS(cpu_), cx, o, v);
  }
}
