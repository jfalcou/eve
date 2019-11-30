//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // x is always positive here TODO an ASSERT in def
  EVE_FORCEINLINE auto  reduce_(EVE_SUPPORTS(cpu_)
                                     , float const &xx) noexcept
  {
    auto x =  abs(xx); 
    if (x <= Pio_4<float>())
    {
      return  std::tuple<float, float, float>(x, 0.0f, 0.0f); 
    }
    if (x <= 120.0f)
    {
      return reduce_fast(x); 
    }
    else
    {
      return reduce_large(x); 
    }
  }
  
  EVE_FORCEINLINE auto  reduce_(EVE_SUPPORTS(cpu_)
                                     , double const &xx) noexcept
  {
    auto x =  abs(xx); 
    if (x <= Pio_4<double>())
    {
      return  std::tuple<double, double, double>(x, 0.0f, 0.0f); 
    }
    if (x <= 120.0f)
    {
      return reduce_fast(x); 
    }
    else
    {
      return reduce_large(x); 
    }
  }
}

#endif
