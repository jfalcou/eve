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
  template<scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  min_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> const& a, wide<T, N> const& b) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric2) || O::contains(pedantic2))
      return min_(EVE_TARGETS(cpu_), opts, a, b);
    else
      return svmin_z(sve_true<T>(),a,b);
  }
}
