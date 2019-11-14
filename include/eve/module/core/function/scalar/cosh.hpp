//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto cosh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    //////////////////////////////////////////////////////////////////////////////
    // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
    // respectively computed
    // *  in the first case cosh (e+rec(e))/2
    // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
    // Threshold is Maxlog - Log_2
    //////////////////////////////////////////////////////////////////////////////
    T x = eve::abs(a0);
    auto test1 = (x > Maxlog<T>()-Log_2<T>());
    T fac = test1 ? Half<T>() : One<T>();
    T tmp = exp(x*fac);
    T tmp1 = Half<T>()*tmp;
    return test1 ? tmp1*tmp : average(tmp, rec(tmp)); 
  }
}

#endif
