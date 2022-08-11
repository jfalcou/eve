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

namespace eve::detail
{
template<floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
trunc_(EVE_SUPPORTS(neon128_), wide<T, N> const& v) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 ) return vrnd_f64(v);
    else if constexpr( cat == category::float64x2 ) return vrndq_f64(v);
    else if constexpr( cat == category::float32x2 ) return vrnd_f32(v);
    else if constexpr( cat == category::float32x4 ) return vrndq_f32(v);
  }
  else return map(trunc, v);
}
}
