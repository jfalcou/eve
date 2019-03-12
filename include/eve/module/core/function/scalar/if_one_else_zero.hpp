//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>

namespace eve::detail
{ 
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_), T const &cond
          , eve::callable_one_ const &
          , eve::callable_zero_ const &
          ) 
  {
    return cond ? One<T>(): Zero<T>();
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_), logical<T> const &cond
          , eve::callable_one_ const &
          , eve::callable_zero_ const &
          ) 
  {
    return cond ? One<T>(): Zero<T>();
  }
    
}



#endif
