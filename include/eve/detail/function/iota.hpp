//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T> EVE_FORCEINLINE constexpr auto linear_ramp(as_<T> const &) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return T(0);
    }
    else
    {
      return T([](auto i, auto) { return i; });
    }
  }
}
