//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_ornot_(EVE_REQUIRES(sve_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return svorn_z(expand_mask(keep_first(N::value), as(a)), a, b);
  }

  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_ornot_(EVE_REQUIRES(sve_), C const& cx, O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return svorn_z(expand_mask(cx, as(a)), a, b);
  }
}
