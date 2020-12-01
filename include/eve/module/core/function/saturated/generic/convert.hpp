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

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////
  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto
  convert_(EVE_SUPPORTS(cpu_), saturated_type const &, IN const &v0, as_<OUT> const &tgt) noexcept
  {
    return convert(saturate(v0, tgt), tgt);
  }
}
