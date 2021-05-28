//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> refine_rec_(EVE_SUPPORTS(neon128_)
                                             , wide<T, N> const& a0
                                             , wide<T, N> const& a1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

         if constexpr( cat == category::float32x2) return vmul_f32(vrecps_f32(a0, a1), a1);
    else if constexpr( cat == category::float32x4) return vmulq_f32(vrecpsq_f32(a0, a1), a1);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1)
      {
        auto x = vmul_f64(vrecps_f64(a0, a1), a1);
        return vmul_f64(vrecps_f64(a0, x), x);
      }
      else if constexpr( cat == category::float64x2)
      {
        auto x = vmulq_f64(vrecpsq_f64(a0, a1), a1);
        return vmulq_f64(vrecpsq_f64(a0, x), x);
      }
    }
    else                                           return map(refine_rec_, a0, a1);
  }
}
