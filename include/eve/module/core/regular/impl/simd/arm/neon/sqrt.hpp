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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/rsqrt.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>  sqrt_(EVE_SUPPORTS(neon128_),
                                    O          const& opts,
                                    wide<T, N> const& v0) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if constexpr(O::contains(lower) || O::contains(upper)) return sqrt.behavior(cpu_{}, opts, v0);
    else if constexpr( current_api >= asimd )
    {
      if      constexpr( cat == category::float32x2 ) return vsqrt_f32(v0);
      else if constexpr( cat == category::float64x1 ) return vsqrt_f64(v0);
      else if constexpr( cat == category::float64x2 ) return vsqrtq_f64(v0);
      else if constexpr( cat == category::float32x4 ) return vsqrtq_f32(v0);
    }
    else
    {
      auto that = if_else(v0, v0 * rsqrt(v0), v0);
      if constexpr( platform::supports_invalids || O::contains(raw))
        return if_else(v0 == inf(as(v0)), v0, that);
      else
        return that;
    }
  }
}
