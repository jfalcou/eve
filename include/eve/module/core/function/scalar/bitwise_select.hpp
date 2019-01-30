//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/bitwise_and.hpp>
#include <eve/function/scalar/bitwise_andnot.hpp>   
#include <eve/function/scalar/bitwise_or.hpp>
#include <type_traits>
#include <iostream>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U> EVE_FORCEINLINE
  constexpr U bitwise_select_(EVE_SUPPORTS(cpu_), T const& a0
                             , U const& a1
                             , U const& a2 ) noexcept
  {
    static_assert ( sizeof(T) == sizeof(U)
                  , "eve::bitwise_select - Arguments have incompatible size"
                  );
    return eve::bitwise_or(eve::bitwise_and(a1, a0), eve::bitwise_andnot(a2,a0));
  }
} 

#endif
