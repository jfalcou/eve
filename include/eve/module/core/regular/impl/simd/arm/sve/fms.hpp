//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fms_(EVE_REQUIRES(sve_),
                                  O const&,
                                  wide<T, N> const& a,
                                  wide<T, N> const& b,
                                  wide<T, N> const& c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return -fnma(a, b, c);
  }

  template<conditional_expr C, scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> fms_(EVE_REQUIRES(sve_),
                                  C const&,
                                  O const& o,
                                  wide<T, N> a,
                                  wide<T, N> b,
                                  wide<T, N> c) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return  fma[o](a, b, -c);
  }
}
