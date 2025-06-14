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
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_not_(EVE_REQUIRES(sve_), O const&, logical<wide<T, N>> a) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return svnot_z(expand_mask(keep_first(N::value), as(a)), a);
  }

  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_not_(EVE_REQUIRES(sve_), C const& cx, O const&, logical<wide<T, N>> a) noexcept
    requires(sve_abi<abi_t<T, N>>)
  {
    return svnot_z(expand_mask(cx, as(a)), a);
  }
}
