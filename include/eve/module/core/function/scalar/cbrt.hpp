//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CBRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CBRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/module/core/detail/generic/cbrt_kernel.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto cbrt_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    
    constexpr double cbtr2 = 1.2599210498948731648;   /* 2^(1/3) */
    constexpr double sqr_cbtr2 = 1.5874010519681994748;   /* 2^(2/3) */
    constexpr T factor[5] =
      {
        1.0 / sqr_cbtr2,
        1.0 / cbtr2,
        1.0,
        cbtr2,
        sqr_cbtr2
      };
    
    if(is_eqz(x) || is_not_finite(x)) return x;
    auto ax =  eve::abs (x); 
    auto test = (ax < 100*Smallestposval<T>());
    if (test) ax = ldexp(ax, 54); 
    /* Reduce X.  XM now is an range 1.0 to 0.5.  */
    auto [xm, xe] = raw_(ifrexp)(ax);
    T u = cbrt_kernel(xm); 
    u *= factor[2 + xe % 3];
    auto exp = sub[test](int(xe)/3, 18); 
    return eve::ldexp(x > 0.0 ? u : -u, exp);
  }

}

#endif
