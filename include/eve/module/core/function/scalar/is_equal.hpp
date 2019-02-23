//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_equal_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept 
  {
    return (a == b);
  }
  
  EVE_FORCEINLINE constexpr bool is_equal_(EVE_SUPPORTS(cpu_)
                                          , bool a
                                          , bool b) noexcept
  {
    return (a == b); 
  }
}

#endif
