//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE  wide<T, N> fam_(EVE_REQUIRES(sve_),
                                   O const&,
                                   wide<T, N> a,
                                   wide<T, N> b,
                                   wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return svmla_x(sve_true<T>(), a, b, c);
  }

  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fam_(EVE_REQUIRES(sve_),
                                  C cond,
                                  O const& o,
                                  wide<T, N> a,
                                  wide<T, N> b,
                                  wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    // We don't care about PEDANTIC as this is a proper FMA.
    // We don't care about PROMOTE as we only accept similar types.
    if      constexpr( C::is_complete && !C::is_inverted )  return alternative(cond, a, as(a));
    else if constexpr(!C::has_alternative)                  return svmla_m(cond.mask(as<T>{}), a, b, c);
    else                                                    return fam.behavior(cpu_{}, o, a, b, c);
  }
}
