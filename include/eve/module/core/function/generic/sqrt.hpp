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

#include <eve/detail/implementation.hpp>
#include <eve/function/raw.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_SUPPORTS(cpu_)
                                  , raw_type const &
                                  , T const &a) noexcept
  {
    return eve::sqrt(a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    if constexpr(has_aggregated_abi_v<T>)
    {
      return aggregate(eve::sqrt, a0);
    }
    else if constexpr(scalar_value<T>)
    {
      return std::sqrt(a0);
    }
    else
    {
      return map(eve::sqrt, a0);
    }
  }
}

