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
  EVE_FORCEINLINE wide<T, N> fsnm_(EVE_REQUIRES(sve_), O const& o, wide<T, N> a, wide<T, N> b,wide<T, N> c) noexcept
  {
    return fnms[o](b, c, a);
  }

  template<conditional_expr C, typename T, typename N, callable_options O>
  requires sve_abi<abi_t<T, N>>
  EVE_FORCEINLINE wide<T, N> fsnm_(EVE_REQUIRES(sve_), C, O const& o, wide<T,N> a, wide<T,N> b, wide<T,N> c) noexcept
  {
    // This is done so the masking use a and not -a as source
    return fsm[o](a, b, minus(c));
  }
}
