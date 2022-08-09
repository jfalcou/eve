//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/ieee_constant.hpp>


namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // centered approximate diff
  template<typename Obj, floating_value T>
  EVE_FORCEINLINE  auto centered_diffdiv(Obj f
                                       , T const &x
                                       ) noexcept
  {
    auto derivexp = (sizeof(element_type_t<T>) == 4) ? -12 :-26;
    auto e = ldexp(one(as(x)), derivexp);
    auto h = eve::max(e*ldexp(one(as(x)), exponent(x)), e);
    return  (f(x+h)-f(x-h))/(h+h);
  }

  template<typename Obj, floating_value T>
  EVE_FORCEINLINE  auto forward_diffdiv(Obj f
                                       , T const &x
                                       ) noexcept
  {
    auto derivexp = (sizeof(element_type_t<T>) == 4) ? -12 :-26;
    auto e = ldexp(one(as(x)), derivexp);
    auto h = eve::max(e*ldexp(one(as(x)), exponent(x)), e);
    return  (f(x+h)-f(x))/(h);
  }

  template<typename Obj, floating_value T>
  EVE_FORCEINLINE  auto backward_diffdiv(Obj f
                                       , T const &x
                                       ) noexcept
  {
    auto derivexp = (sizeof(element_type_t<T>) == 4) ? -12 :-26;
    auto e = ldexp(one(as(x)), derivexp);
    auto h = eve::max(e*ldexp(one(as(x)), exponent(x)), e);
    return  (f(x)-f(x-h))/(h);
  }
}
