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
  EVE_FORCEINLINE constexpr wide<T,N>
  if_else_(EVE_REQUIRES(sve_), O, logical<wide<T,N>> m, wide<T,N> v0, wide<T,N> v1) noexcept
  requires sve_abi<abi_t<T,N>>
  {
    return svsel(m, v0, v1);
  }

  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_REQUIRES(sve_), O, logical<wide<T,N>> m, logical<wide<T,N>> v0, logical<wide<T,N>> v1) noexcept
  requires sve_abi<abi_t<T,N>>
  {
    return svsel(m, v0, v1);
  }
}
