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

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> sqrt_(EVE_SUPPORTS(neon128_)
                                       , raw_type const &
                                       , wide<T, N, ABI> const& v0) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#  if defined(__aarch64__)
         if constexpr( cat == category::float32x2) return vsqrt_f32(v);
    else if constexpr( cat == category::float32x4) return vsqrtq_f32(v);
    else if constexpr( cat == category::float64x1) return vsqrt_f64(v);
    else if constexpr( cat == category::float64x2) return vsqrtq_f64(v);
#  else
         if constexpr( cat == category::float32x2) return if_else(v0, v0 * raw(rsqrt)(v0), v0);
    else if constexpr( cat == category::float32x4) return if_else(v0, v0 * raw(rsqrt)(v0), v0);
#  endif
    else                                           return map(sqrt, v0);
  }

  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rec_(EVE_SUPPORTS(neon128_),
                                       wide<T, N, ABI> const &v0) noexcept
  {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw(rec)(v0));
      return refine_rec(v0, a);
  }
}


  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> sqrt_(EVE_SUPPORTS(neon128_)
                                       , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#  if defined(__aarch64__)
    if constexpr( cat == category::float32x2) return vsqrt_f32(v);
    else if constexpr( cat == category::float32x4) return vsqrtq_f32(v);
    else if constexpr( cat == category::float64x1) return vsqrt_f64(v);
    else if constexpr( cat == category::float64x2) return vsqrtq_f64(v);
#  else
    if constexpr( (cat == category::float32x2) ||  (cat == category::float32x4))
    {
      auto that = if_else(v0, v0 * raw(rsqrt)(v0), v0);
      if constexpr(platform::supports_invalids) { return if_else(is_not_finite(v0), v0, that); }
    }
#  endif
    else                                           return map(ceil, v);
  }
}
