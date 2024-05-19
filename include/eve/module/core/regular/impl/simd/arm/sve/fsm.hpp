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
  template<typename T, typename N, callable_options O>
  requires sve_abi<abi_t<T, N>>
  EVE_FORCEINLINE wide<T, N> fsm_(EVE_REQUIRES(sve_), O const&, wide<T, N> a, wide<T, N> b,wide<T, N> c) noexcept
  {
    return -fanm(a, b, c);
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  requires sve_abi<abi_t<T, N>>
  EVE_FORCEINLINE wide<T, N> fsm_(EVE_REQUIRES(sve_), C m, O const&, wide<T,N> a, wide<T,N> b, wide<T,N> c) noexcept
  {
    // This is done so the masking use a and not -a as source
    // We don't care about PEDANTIC as this is a proper FMA.
    // We don't care about PROMOTE as we only accept similar types.
    [[maybe_unused]] auto const alt = alternative(m, a, as(a));
    if      constexpr( C::is_complete )       return alt;
    else if constexpr( !C::has_alternative )  return minus[m](wide<T, N>(svmls_m(m.mask(as<T>{}), a, b, c)));
    else                                      return if_else(m, -eve::fanm(a, b, c), alt);
  }
}
