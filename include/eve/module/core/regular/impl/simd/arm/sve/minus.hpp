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
  template<callable_options O, signed_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> minus_(EVE_REQUIRES(sve_), O const& o, wide<T, N> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    // saturated integer has no intrinsic and floating is better by default
    if constexpr((O::contains(saturated2) && std::integral<T>) || floating_value<T>) return minus.behavior(cpu_{},o,v);
    else                                                                             return svneg_x(sve_true<T>(),v);
  }

  template<callable_options O, conditional_expr C, signed_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> minus_(EVE_REQUIRES(sve_), C const& mask, O const& o, wide<T, N> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, v, as(v));

    // ignore all just return alternative
    if constexpr( C::is_complete ) return alt;
    else
    {
      //  if saturated on integer, we don't have masked op so we delegate
      if constexpr(O::contains(saturated2) && std::integral<T>) return minus.behavior(cpu_{},o,v);
      else                                                      return svneg_m(alt,expand_mask(mask, as(v)),v);
    }
  }
}
