//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T
  opsub(T const& a, T b) noexcept
  {
    if constexpr(scalar_value<T>) return T(a-b);
    else return a-b;
  }
}
