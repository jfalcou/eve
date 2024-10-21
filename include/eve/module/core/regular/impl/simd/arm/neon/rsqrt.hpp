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
                                    O          const &o,
                                    wide<T, N> w) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    using that_t       = wide<T, N>;
    constexpr auto cat = categorize<that_t>();
    if constexpr(O::contains(pedantic))
    {
      return rsqrt.behavior(as<wide<T, N>>{}, cpu_{}, o, w);
    }
    else if constexpr(O::contains(raw))
    {
      if      constexpr( cat == category::float32x2 ) return vrsqrte_f32(w);
      else if constexpr( cat == category::float32x4 ) return vrsqrteq_f32(w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 ) return vrsqrte_f64(w);
        else if constexpr( cat == category::float64x2 ) return vrsqrteq_f64(w);
      }
      else return map(as<wide<T, N>>{}, rsqrt, w);
    }
    else
    {
      if constexpr( cat == category::float32x2 )
      {
        that_t inv = vrsqrte_f32(w);
        inv        = vmul_f32(vrsqrts_f32(w, inv * inv), inv);
        return that_t(vmul_f32(vrsqrts_f32(w, inv * inv), inv));
      }
      else if constexpr( cat == category::float32x4 )
      {
        that_t inv = vrsqrteq_f32(w);
        inv        = vmulq_f32(vrsqrtsq_f32(w, inv * inv), inv);
        return that_t(vmulq_f32(vrsqrtsq_f32(w, inv * inv), inv));
      }
      else if constexpr( current_api >= asimd )
      {
        if constexpr( cat == category::float64x1 )
        {
          that_t inv = vrsqrte_f64(w);
          inv        = vmul_f64(vrsqrts_f64(w, inv * inv), inv);
          inv        = vmul_f64(vrsqrts_f64(w, inv * inv), inv);
          return that_t(vmul_f64(vrsqrts_f64(w, inv * inv), inv));
        }
        else if constexpr( cat == category::float64x2 )
        {
          that_t inv = vrsqrteq_f64(w);
          inv        = vmulq_f64(vrsqrtsq_f64(w, inv * inv), inv);
          inv        = vmulq_f64(vrsqrtsq_f64(w, inv * inv), inv);
          return that_t(vmulq_f64(vrsqrtsq_f64(w, inv * inv), inv));
        }
      }
      else return map(as<wide<T, N>>{}, rsqrt, w);
    }
  }
}
