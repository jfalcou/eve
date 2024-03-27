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
  EVE_FORCEINLINE wide<T, N> floor_(EVE_REQUIRES(neon128_),
                                    O const&,
                                    wide<T, N> const& v) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr(!O::contains(tolerance))
    {
      constexpr auto cat = categorize<wide<T, N>>();
      if constexpr( current_api >= asimd )
      {
             if constexpr( cat == category::float64x1 ) return vrndm_f64(v);
        else if constexpr( cat == category::float64x2 ) return vrndmq_f64(v);
        else if constexpr( cat == category::float32x2 ) return vrndm_f32(v);
        else if constexpr( cat == category::float32x4 ) return vrndmq_f32(v);
      }
      else return map(floor, v);
    }
    else
      return floor_(EVE_TARGETS(cpu_), cx, o, v);
  }
}
