//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/saturated.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////
  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto
  convert_(EVE_SUPPORTS(cpu_), saturated_type const &, IN const &v0, as<OUT> const &tgt) noexcept
  {
    return convert(saturate(v0, tgt), tgt);
  }
}
