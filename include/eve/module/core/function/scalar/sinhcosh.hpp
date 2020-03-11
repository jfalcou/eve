//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINHCOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINHCOSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/div.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sinhcosh_(EVE_SUPPORTS(cpu_)
                                          , T a0) noexcept
  requires(std::tuple<T, T>, floating_point<T>)
  {
    T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
    auto x = eve::abs(a0);
    if (x < T(0x1.0p-28)) return std::make_tuple(a0, One<T>());
    auto h = (a0 > T(0)) ? T(1) : T(-1);
    if (x >= ovflimit)
    {
      auto w = exp(x*Half<T>());
      auto t = Half<T>()*w;
      t *= w;
      return std::make_tuple(t*h, t); 
    }
    h*= Half<T>(); 
    auto t = expm1(x);
    auto inct = inc(t); 
    auto u = t/inct;
    auto s = h*(fnma(t, u, t)+t);
    auto c = (x > T(22.0f)) ? inct*Half<T>() : average(inct, rec(inct)); 
    return std::make_tuple(s, c); 
  }
}

#endif
/* Method for cosh
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 *  1. Replace x by |x| (cosh(x) = cosh(-x)).
 *  2.
 *                                              exp(x) +  1/exp(x)
 *      0    <= x <= 22:             cosh(x) := -------------------
 *                                                      2
 *      22       <= x <= ovflimit:   cosh(x) := exp(x)/2
 *      ovflimit <= x:               cosh(x) := exp(x/2)/2 * exp(x/2)
 */
/* Method for sinh
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 *  1. Replace x by |x| (sinh(-x) = -sinh(x)).
 *  2.
 *                                                 E + E/(E+1)
 *      0        <= x <= 22:          sinh(x) := --------------, E=expm1(x)
 *                                                      2
 *
 *      22       <= x <=  ovflimit:   sinh(x) := exp(x)/2
 *      ovflimit <= x:                sinh(x) := exp(x/2)/2 * exp(x/2)
 */
