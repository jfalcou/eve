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
  EVE_FORCEINLINE wide<T, N>
  rec_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v) noexcept
  requires (arm_abi<abi_t<T, N>>)
  {

    if constexpr(O::contains(lower) || O::contains(upper))
      return rec.behavior(cpu_{}, opts, v);
    else if constexpr(O::contains(raw))
    {
      constexpr auto cat = categorize<wide<T, N>>();

      if constexpr (std::same_as<T, eve::float16_t>)
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32(eve::rec, v);
        else if constexpr (cat == category::float16x8)        return vrecpeq_f16(v);
        else if constexpr (cat == category::float16x4)        return vrecpe_f16(v);
      }
      else if constexpr( cat == category::float32x2 ) return vrecpe_f32(v);
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
