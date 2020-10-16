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
#include <eve/constant/zero.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template < typename T, typename A> auto poleval(T x, A const & coefs)
  {
    auto p = coefs.begin();
    auto r = T(*p++);

    while(p!= coefs.end())
    {
      r = fma(r, x,  *p++);
    }
    return r;
  }

  template < typename T, typename A> auto poleval1(T x, A const & coefs)
  {
    auto p = coefs.begin();
    auto r = x+T(*p++);
    
    while(p!= coefs.end())
    {
      r = fma(r, x,  *p++);
    }
    return r;
  }


}
