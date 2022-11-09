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
template<scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
if_else_(EVE_SUPPORTS(sve_),
         logical<wide<T, N>> const& c,
         wide<T, N> const& vt,
         wide<T, N> const& vf) noexcept
requires sve_abi<abi_t<T, N>>
{
  return svsel(c, vt, vf);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
if_else_(EVE_SUPPORTS(sve_),
         logical<wide<T, N>> const& c,
         logical<wide<T, N>> const& vt,
         logical<wide<T, N>> const& vf) noexcept
requires sve_abi<abi_t<T, N>>
{
  return svsel(c, vt, vf);
}
}
