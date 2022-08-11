//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/raw.hpp>

namespace eve::detail
{
template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
rec_(EVE_SUPPORTS(neon128_), raw_type const&, wide<T, N> v) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( cat == category::float32x2 ) return vrecpe_f32(v);
  else if constexpr( cat == category::float32x4 ) return vrecpeq_f32(v);
  else if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 ) return vrecpe_f64(v);
    else if constexpr( cat == category::float64x2 ) return vrecpeq_f64(v);
  }
  else return T {1} / v;
}

template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                rec_(EVE_SUPPORTS(neon128_), wide<T, N> v0) noexcept requires arm_abi<abi_t<T, N>>
{
  return T {1} / v0;
}
}
