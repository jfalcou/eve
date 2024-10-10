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
                                    wide<T, N> w) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if constexpr(O::contains(lower) || O::contains(upper)) return sqrt.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    else if constexpr( current_api >= asimd )
    {
      if      constexpr( cat == category::float32x2 ) return vsqrt_f32(w);
      else if constexpr( cat == category::float64x1 ) return vsqrt_f64(w);
      else if constexpr( cat == category::float64x2 ) return vsqrtq_f64(w);
      else if constexpr( cat == category::float32x4 ) return vsqrtq_f32(w);
    }
    else
    {
      auto that = if_else(w, w * rsqrt(w), w);
      if constexpr( platform::supports_invalids || O::contains(raw))
        return if_else(w == inf(as{w}), w, that);
      else
        return that;
    }
  }
}
