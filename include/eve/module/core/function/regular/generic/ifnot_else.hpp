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
#include <eve/function/if_else.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T, value U, value V>
  EVE_FORCEINLINE constexpr auto ifnot_else_(EVE_SUPPORTS(cpu_)
             , T const &cond
             , U const &t
             , V const &f) noexcept
  requires compatible_values<U, V>
  {
    return if_else(cond, f, t);
  }
}

