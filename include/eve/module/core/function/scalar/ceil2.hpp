//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/floor2.hpp>
#include <eve/function/if_else.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ceil2_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  requires(T, floating_point<T>)
  {
    if (v <= One(as(v))) return One(as(v)); 
    if (is_less(v, One(as(v)))) return Zero(as(v)); 
    auto [m, e] = ifrexp(v);
    e = dec(e); 
    auto tmp = ldexp(One(as(v)), e); 
    return (tmp < v) ? tmp*2 : tmp; 
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto ceil2_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  requires(T, unsigned_type<T>)
  {
    if (v <= One(as(v))) return One(as(v)); 
    auto tmp =  floor2(v);
    return (tmp < v) ? tmp*2 :  tmp; 
  }
  
}

#endif
