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
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                div_(EVE_SUPPORTS(sse2_),
                     C const                         &cx,
                     wide<T, N> const                &v,
                     wide<T, N> const                &w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return div_(EVE_RETARGET(cpu_), cx, v, w);
  }
  else
  {
    auto src = alternative(cx, v, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( c == category::float32x16 ) return _mm512_mask_div_ps(src, m, v, w);
    else if constexpr( c == category::float64x8 ) return _mm512_mask_div_pd(src, m, v, w);
    else { return div_(EVE_RETARGET(cpu_), cx, v, w); }
  }
}
}
