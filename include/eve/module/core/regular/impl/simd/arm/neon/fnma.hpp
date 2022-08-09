//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fnma_(EVE_SUPPORTS(neon128_),
                      wide<T, N> const                &v0,
                      wide<T, N> const                &v1,
                      wide<T, N> const                &v2) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( cat == category::float32x2 ) return vfms_f32(v2, v1, v0);
  else if constexpr( cat == category::float32x4 ) return vfmsq_f32(v2, v1, v0);
  else if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 ) return vfms_f64(v2, v1, v0);
    else if constexpr( cat == category::float64x2 ) return vfmsq_f64(v2, v1, v0);
    else return fma(-v0, v1, v2);
  }
  else return fma(-v0, v1, v2);
}
}
