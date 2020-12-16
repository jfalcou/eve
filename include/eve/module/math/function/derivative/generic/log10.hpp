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

#include <eve/function/derivative/log.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log10_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    auto invlog10 = T(0.4342944819032518276511289189);
    return if_else(is_gtz(x), rec(x)*invlog10, allbits); ;
  }
}
