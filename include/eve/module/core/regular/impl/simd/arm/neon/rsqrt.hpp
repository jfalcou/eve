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
#include <eve/traits/apply_fp16.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_REQUIRES(neon128_),
                                    O          const &o,
                                    wide<T, N> const &v0) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    using that_t       = wide<T, N>;
    constexpr auto cat = categorize<that_t>();
    if constexpr(O::contains(pedantic))
    {
      return rsqrt.behavior(cpu_{}, o, v0);
    }
    else if constexpr(O::contains(raw))
    {
      if constexpr (std::same_as<T, eve::float16_t>)
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32(eve::rsqrt, v0);
        else if constexpr (cat == category::float16x8)        return vrsqrteq_f16(v0);
        else if constexpr (cat == category::float16x4)        return vrsqrte_f16(v0);
      }
      else if constexpr( cat == category::float32x2 ) return vrsqrte_f32(v0);
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
      if constexpr (std::same_as<T, eve::float16_t>)
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32(eve::rsqrt, v0);
        else if constexpr (cat == category::float16x8)
        {
          that_t inv = vrsqrteq_f16(v0);
          inv        = vmulq_f16(vrsqrtsq_f16(v0, inv * inv), inv);
          return that_t(vmulq_f16(vrsqrtsq_f16(v0, inv * inv), inv));
        }
        else if constexpr (cat == category::float16x4)
        {
          that_t inv = vrsqrte_f16(v0);
          inv        = vmul_f16(vrsqrts_f16(v0, inv * inv), inv);
          return that_t(vmul_f16(vrsqrts_f16(v0, inv * inv), inv));
        }
      }
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
