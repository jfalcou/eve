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
  EVE_FORCEINLINE logical<wide<T, N>> logical_xor_(EVE_REQUIRES(sve_), O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return sveor_z(expand_mask(keep_first(N::value), as(a)), a, b);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_xor_(EVE_REQUIRES(sve_), auto const& cx, O const&, logical<wide<T, N>> a, logical<wide<T, N>> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return sveor_z(expand_mask(cx, as(a)), a, b);
  }
}
