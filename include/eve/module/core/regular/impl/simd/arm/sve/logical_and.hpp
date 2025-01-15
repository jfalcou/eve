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
  EVE_FORCEINLINE logical<wide<T, N>> logical_and_(EVE_REQUIRES(sve_), O const&, logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept
    requires(sve_abi<abi_t<T, N>>)
  {
    return svmov_z(v, w);
  }
}
