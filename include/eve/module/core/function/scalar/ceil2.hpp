//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/ceil.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ceil2_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      return exp2(ceil(a0));
    }
    else 
    {
      T count = 0; 
      if (a0 && !(a0 & (a0 - 1))) return a0;  
      
      while( a0 != 0)  
      {  
        a0 >>= 1;  
        ++count;  
      }  
      
      return 1 << count;
    }
  }
}

#ea0dif
