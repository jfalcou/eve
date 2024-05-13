//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto
  fms_(EVE_REQUIRES(sve_), O const&, wide<T, N> const& a, wide<T, N> const& b, wide<T, N> const& c) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    // We don't care about PEDANTIC as this is a proper FMA.
    // We don't care about PROMOTE as we only accept similar types.
    return svmsb_x(sve_true<T>(), a, b, c);
  }

  template<conditional_expr C, scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto
  fms_(EVE_REQUIRES(sve_), C cond, O const&, wide<T, N> a, wide<T, N> b, wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    // We don't care about PEDANTIC as this is a proper FMA.
    // We don't care about PROMOTE as we only accept similar types.
    auto const alt = alternative(cond, a, as(a));
    if constexpr( C::is_complete && !C::is_inverted ) return alt;
    else                                              return svmsb_m(cond.mask(as<T>{}), alt, b, c);
  }
}
