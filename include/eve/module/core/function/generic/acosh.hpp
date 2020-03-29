//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/add.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acosh_(EVE_SUPPORTS(cpu_)
                                       , T x) noexcept
  {
    if constexpr(native<T>)
    {
      T t = dec(x);
      auto test = is_greater(t,Oneotwoeps<T>());
      if constexpr(simd_value<T>)
      {
        T z = if_else(test, x, t+sqrt(t+t+sqr(t)));
        return add[test](log1p(z), Log_2<T>());    
      }
      else if constexpr(scalar_value<T>)
      {   
        if(test) return eve::log1p(t+eve::sqrt(t+t+sqr(t)));
        else     return eve::log(t)+Log_2<T>();
      }
    }
    else return apply_over(acosh, x);
  }  
}

#endif
