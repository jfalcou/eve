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

#include <eve/function/log_abs.hpp>
#include <eve/function/derivative/log.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/all.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T log_abs_(EVE_SUPPORTS(cpu_)
                                     , derivative_type<1> const &
                                     , T x
                                     , N n) noexcept
  {
    return derivative(log)(eve::abs(x), n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log_abs_(EVE_SUPPORTS(cpu_)
                                     , derivative_type<1> const &
                                     , T x) noexcept
  {
    return rec(x);
  }
}
