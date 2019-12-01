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
#include <eve/function/is_nltz.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template < typename T>
  EVE_FORCEINLINE auto  reduce_(EVE_SUPPORTS(cpu_)
                                     , T const &x) noexcept
  {
    EVE_ASSERT(is_nltz(x), "attempted reduce with negative argument"); 
    if (x <= Pio_4<T>()) return  std::tuple<T, T, T>(T(0), x, T(0)); 
    else
    {
      if constexpr(std::is_same_v<T, float>)
      {                   
        if (x <= 200.0f)  return reduce_fast(x); 
        else if (x <= 1.89e+15f) return reduce_medium(x); 
        else return reduce_large(x); 
      }
      else if constexpr(std::is_same_v<T, double>)
      {
        if (x <= 200.0f)  return reduce_fast(x); 
        else if (x <=  281474976710656.0) return reduce_medium(x); 
        else return reduce_large(x); 
      }
    }
  }
}

#endif
