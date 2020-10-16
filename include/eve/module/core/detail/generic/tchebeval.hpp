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

#include <eve/detail/overload.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/average.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template < typename T, typename A> auto tchebeval(T x, A const & coefs)
  {
    auto p = coefs.begin();
    T b0 = T(*p++);
    T b1 = eve::zero(eve::as(b0));
    T b2 = eve::zero(eve::as(b0)); ;

    while(p!= coefs.end())
    {
      b2 = -b1;
      b1 = b0;
      b0 = eve::fma(x, b1, b2 + *p++);
    }
    return eve::average(b0, b2);
  }


}
