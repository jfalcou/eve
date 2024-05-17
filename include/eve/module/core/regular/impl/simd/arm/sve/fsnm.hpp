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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fsnm_(EVE_REQUIRES(sve_),
                                   O const&,
                                   wide<T, N> a,
                                   wide<T, N> b,
                                   wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return -fam(a, b, c);
  }

  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>  fsnm_(EVE_REQUIRES(sve_),
                                    C const &,
                                    O const & o,
                                    wide<T, N> a,
                                    wide<T, N> b,
                                    wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return fsm[o](a, -b, c);
  }
}
