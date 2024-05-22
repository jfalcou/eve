//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<callable_options O, scalar_value T, integral_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T,N> lookup_(EVE_REQUIRES(sve_), O const&, wide<T,N> a, wide<I,N> i) noexcept
  requires(sve_abi<abi_t<I, N>> && sve_abi<abi_t<T, N>>)
  {
    return wide<T, N>{svtbl(a, convert(i, uint_from<T>{}))};
  }
}
