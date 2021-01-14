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

#include <eve/function/exp.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T logspace_add_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return rec(inc(exp(y-x)));
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T logspace_add_(EVE_SUPPORTS(cpu_)
                                   , diff_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return  rec(inc(exp(x-y)));
  }
}
