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
  EVE_FORCEINLINE auto fnms_(EVE_REQUIRES(sve_),
                             O const&,
                             wide<T, N> v0, wide<T, N> v1,
                             wide<T, N> v2) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    return -svmad_x(sve_true<T>(), v0, v1, v2);
  }

  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto  fnms_(EVE_REQUIRES(sve_),
                              C cond,
                              O const&,
                              wide<T, N> v0,
                              wide<T, N> v1,
                              wide<T, N> v2) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    if      constexpr( C::is_complete && !C::is_inverted )  return alternative(cond, a, as(a));
    else if constexpr(!C::has_alternative)                  return -svmad_m(cond.mask(as<T>{}), a, b, c);
    else                                                    return fnms.behavior(cpu_{}, opts, a, b, c);
  }
}
