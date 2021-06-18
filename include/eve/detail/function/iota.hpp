//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto linear_ramp(as<T> const &) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return T(0);
    }
    else
    {
      return T([](auto i, auto ) { return i; } );
    }
  }
}

