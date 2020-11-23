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

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rsqrt_(EVE_SUPPORTS(neon128_)
                                        , raw_type const &
                                        , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr( cat == category::float32x2) return vrsqrte_f32(v);
    else if constexpr( cat == category::float32x4) return vrsqrteq_f32(v);
#  if defined(__aarch64__)
    else if constexpr( cat == category::float64x1) return vrsqrte_f64(v);
    else if constexpr( cat == category::float64x2) return vrsqrteq_f64(v);
#  endif
    else                                           return map(rsqrt, v);
  }

  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rsqrt_(EVE_SUPPORTS(neon128_)
                                        , wide<T, N, ABI> const& v0) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();
    using that_t = wide<T, N, ABI>;

          if constexpr( cat == category::float32x2)
    {
      that_t inv  = vrsqrte_f32(v0);
      inv         = vmul_f32(vrsqrts_f32(v0, inv * inv), inv);
      return that_t(vmul_f32(vrsqrts_f32(v0, inv * inv), inv));
    }
    else if constexpr( cat == category::float32x4)
    {
      that_t inv  = vrsqrteq_f32(v0);
      inv         = vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv);
      return that_t(vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv));
    }
#  if defined(__aarch64__)
    else if constexpr( cat == category::float64x1)
    {
      that_t inv  = vrsqrte_f64(v0);
      inv         = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
      inv         = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
      return that_t(vmul_f64(vrsqrts_f64(v0, inv * inv), inv));
    }
    else if constexpr( cat == category::float64x2)
    {
      that_t inv  = vrsqrteq_f64(v0);
      inv         = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
      inv         = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
      return that_t(vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv));
    }
#  endif
    else return map(rsqrt, v0);
  }
}
