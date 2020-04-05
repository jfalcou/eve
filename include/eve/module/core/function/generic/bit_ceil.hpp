//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_CEIL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_CEIL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_floor.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_ceil_(EVE_SUPPORTS(cpu_)
                                , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
      auto vle1 = v <= One(as(v)); 
      if constexpr(scalar_value<T>) if (vle1) return One(as(v));
      if constexpr(floating_real_value<T>)
      {
        auto [m, e] = ifrexp(v);
        e = dec(e); 
        auto tmp = ldexp(One(as(v)), e);
        auto tmpltv = tmp < v; 
        if constexpr(scalar_value<T>)
        {
          return tmpltv ? tmp*2 : tmp;
        }
        else
        {
          return if_else(vle1, One(as(v)), if_else(tmpltv,  tmp*2, tmp));
        }
      }
      else
      {
        auto tmp =  bit_floor(v);
        auto tmpltv = tmp < v; 
        if constexpr(scalar_value<T>)  return T(tmpltv ? tmp*2 :  tmp);
        else return if_else(vle1, One(as(v)) //TODO Optimize with one_ ?
                           , if_else(tmpltv, tmp*2,  tmp)); 
      }
    }
    else return apply_over(bit_ceil, v); 
  }
}

#endif
