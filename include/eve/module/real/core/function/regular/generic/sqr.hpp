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
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    return a * a;
  }
}
