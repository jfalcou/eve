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
template<scalar_value T, integral_scalar_value I, typename N>
EVE_FORCEINLINE auto
lookup_(EVE_SUPPORTS(sve_), wide<T, N> a, wide<I, N> i) noexcept
requires(sve_abi<abi_t<I, N>> && sve_abi<abi_t<T, N>>)
{
  auto idx = convert(i, as<as_integer_t<T, unsigned>> {});
  return wide<T, N>{svtbl(a, idx)};
}

template<scalar_value T, integral_scalar_value I, typename N>
EVE_FORCEINLINE auto
lookup_(EVE_SUPPORTS(sve_), logical<wide<T, N>> a, wide<I, N> i) noexcept
requires(sve_abi<abi_t<I, N>> && sve_abi<abi_t<T, N>>)
{
  return to_logical(lookup(a.mask(), i));
}
}
