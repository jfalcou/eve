//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/add.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T plus_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return a;
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto plus_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  -> decltype( eve::add(a,b) )
  {
    return eve::add(a, b); 
  }

  template<typename C, typename T, typename U>
  EVE_FORCEINLINE constexpr auto plus_(EVE_SUPPORTS(cpu_), C const & cond, T const &a, U const &b) noexcept
  -> decltype( eve::add[cond](a,b) )
  {
    return eve::add[cond](a, b); 
  }  
}

#endif
