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

#include <eve/constant/one.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T , T y ) noexcept
  {

    return rec(y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x, T y ) noexcept
  {

    return -rec(sqr(y))*x;
  }
}
