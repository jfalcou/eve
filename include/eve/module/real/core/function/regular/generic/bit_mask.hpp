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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_nez.hpp>

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return is_nez(v).mask();
  }
}
