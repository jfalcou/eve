//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sinh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
    auto x = eve::abs(a0);
    if (is_eqz(a0)) return a0;
    auto h = (a0 > T(0)) ? T(1) : T(-1);
    if (x >= ovflimit)
    {
      auto w = exp(x*Half<T>());
      auto t = Half<T>()*w;
      t *= w;
      return t*h; 
    }
    h*= Half<T>(); 
    auto t = expm1(x);
    auto inct = inc(t); 
    auto u = t/inct;
    auto s = h*(fnma(t, u, t)+t);
    return s; 
  }
}

#endif
