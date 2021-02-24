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
#include <eve/function/fma.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fnma_(EVE_SUPPORTS(neon128_),
                                        wide<T, N, ABI> const &v0,
                                        wide<T, N, ABI> const &v1,
                                        wide<T, N, ABI> const &v2) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

         if constexpr(  cat == category::float32x2) return vfms_f32(v2, v1, v0);
    else if constexpr(  cat == category::float32x4) return vfmsq_f32(v2, v1, v0);
    else if constexpr( current_api >= asimd)
    {
            if constexpr(  cat == category::float64x1)  return vfms_f64(v2, v1, v0);
      else  if constexpr(  cat == category::float64x2)  return vfmsq_f64(v2, v1, v0);
      else                                              return fma(-v0, v1, v2);
    }
    else                                            return fma(-v0, v1, v2);
  }
}
