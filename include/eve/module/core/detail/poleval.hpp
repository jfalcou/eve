//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/one.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template < typename T, typename A> auto poleval(T x, A const & coefs)
  {
    auto p = coefs.begin();
    if(coefs.end() == p) return zero(as(x));
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
    if(coefs.end() == p) return one(as(x));
    auto r = x+T(*p++);

    while(p!= coefs.end())
    {
      r = fma(r, x,  *p++);
    }
    return r;
  }


}
