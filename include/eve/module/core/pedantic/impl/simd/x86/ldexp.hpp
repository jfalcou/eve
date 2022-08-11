//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                ldexp_(EVE_SUPPORTS(avx512_),
                       pedantic_type const&,
                       wide<T, N> a0,
                       wide<T, N> a1) noexcept requires x86_abi<abi_t<T, N>>
{
  return ldexp(a0, a1);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                ldexp_(EVE_SUPPORTS(avx512_),
                       C const                &cx,
                       pedantic_type const&,
                       wide<T, N> const                &v,
                       wide<T, N> const                &w) noexcept requires x86_abi<abi_t<T, N>>
{
  return ldexp[cx](v, w);
}

}
