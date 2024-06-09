//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_REQUIRES(neon128_),
                                    O          const &,
                                    wide<T, N> const &v0) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(raw2))
    {
      using that_t       = wide<T, N>;
      constexpr auto cat = categorize<that_t>();

      if      constexpr( cat == category::float32x2 ) return vrsqrte_f32(v0);
      else if constexpr( cat == category::float32x4 ) return vrsqrteq_f32(v0);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 ) return vrsqrte_f64(v0);
        else if constexpr( cat == category::float64x2 ) return vrsqrteq_f64(v0);
      }
      else return map(rsqrt, v0);
    }
    else
    {
      if constexpr( cat == category::float32x2 )
      {
        that_t inv = vrsqrte_f32(v0);
        inv        = vmul_f32(vrsqrts_f32(v0, inv * inv), inv);
        return that_t(vmul_f32(vrsqrts_f32(v0, inv * inv), inv));
      }
      else if constexpr( cat == category::float32x4 )
      {
        that_t inv = vrsqrteq_f32(v0);
        inv        = vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv);
        return that_t(vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv));
      }
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 )
        {
          that_t inv = vrsqrte_f64(v0);
          inv        = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
          inv        = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
          return that_t(vmul_f64(vrsqrts_f64(v0, inv * inv), inv));
        }
        else if constexpr( cat == category::float64x2 )
        {
          that_t inv = vrsqrteq_f64(v0);
          inv        = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
          inv        = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
          return that_t(vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv));
        }
      }
      else return map(rsqrt, v0);
    }
  }
}
