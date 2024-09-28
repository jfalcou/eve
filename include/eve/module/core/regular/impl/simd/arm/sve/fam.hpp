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
  template<typename T, typename N, callable_options O>
  requires sve_abi<abi_t<T, N>>
  EVE_FORCEINLINE wide<T, N> fam_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> a, wide<T, N> b, wide<T, N> c) noexcept
  {
    // We don't care about PEDANTIC as this is a proper FMA.
    // We don't care about PROMOTE as we only accept similar types.
    if constexpr(O::contains(lower) || O::contains(upper))
      return fam.behavior(cpu_{}, opts, a, b, c);
    else
      return svmla_x(sve_true<T>(), a, b, c);
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  requires sve_abi<abi_t<T, N>>
  EVE_FORCEINLINE wide<T, N> fam_(EVE_REQUIRES(sve_), C cond, O const& opts, wide<T,N> a, wide<T,N> b, wide<T,N> c) noexcept
  {
    if constexpr(O::contains(lower) || O::contains(upper))
      return fam.behavior(cpu_{}, opts, a, b, c);
    else
    {
      // We don't care about PEDANTIC as this is a proper FMA.
      // We don't care about PROMOTE as we only accept similar types.
      [[maybe_unused]] auto const alt = alternative(cond, a, as(a));
      if      constexpr( C::is_complete )       return alt;
      else if constexpr( !C::has_alternative )  return svmla_m(cond.mask(as<T>{}), a, b, c);
      else                                      return if_else(cond, eve::fam(a, b, c), alt);
    }
  }
}
