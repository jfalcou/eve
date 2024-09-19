//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires arm_abi<abi_t<T, N>>
{
  if constexpr (O::contains(saturated))
  {
    return div.behavior(cpu_{}, opts, a, b);
  }
  else if constexpr (O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
  {
    return div.behavior(cpu_{}, opts, a, b);
  }
  else
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr (current_api >= asimd)
    {
            if constexpr( c == category::float64x1 ) return vdiv_f64 (a, b);
      else  if constexpr( c == category::float64x2 ) return vdivq_f64(a, b);
      else  if constexpr( c == category::float32x2 ) return vdiv_f32 (a, b);
      else  if constexpr( c == category::float32x4 ) return vdivq_f32(a, b);
      else
      {
        return div.behavior(cpu_{}, opts, a, b);
      }
    }
    else if constexpr (std::same_as<T, float>)
    {
      auto estimate = [](auto x)
      {
              if constexpr( c == category::float32x2 ) return vrecpe_f32(x);
        else  if constexpr( c == category::float32x4 ) return vrecpeq_f32(x);
      };

      auto refine = [](auto x, auto y) -> wide<T, N>
      {
              if constexpr( c == category::float32x2 ) return vmul_f32(vrecps_f32(x, y), y);
        else  if constexpr( c == category::float32x4 ) return vmulq_f32(vrecpsq_f32(x, y), y);
      };

      return a * refine(b, refine(b, estimate(b)));
    }
    else if constexpr( current_api >= asimd && std::same_as<T, double> )
    {
      auto estimate = [](auto x)
      {
              if constexpr( c == category::float64x1 ) return vrecpe_f64(x);
        else  if constexpr( c == category::float64x2 ) return vrecpeq_f64(x);
      };

      auto refine = [](auto x, auto y) -> wide<T, N>
      {
              if constexpr( c == category::float64x1 ) return vmul_f64(vrecps_f64(x, y), y);
        else  if constexpr( c == category::float64x2 ) return vmulq_f64(vrecpsq_f64(x, y), y);
      };

      return a * refine(b, refine(b, estimate(b)));
    }
    else
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
  }
}

}
