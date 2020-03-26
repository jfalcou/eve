//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto cosh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires std::floating_point<T>
  {
    T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
    auto x = eve::abs(a0);
    if (is_eqz(a0)) return One<T>();
    if (x >= ovflimit-Log_2<T>())
    {
      auto w = exp(x*Half<T>());
      auto t = Half<T>()*w;
      t *= w;
      return t; 
    }
    auto t = exp(x);
    return (x > T(22.0f)) ? t*Half<T>() : average(t, rec(t)); 
  }
}

#endif
