//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp> 
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/function/scalar/is_nez.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/is_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_denormal_(EVE_SUPPORTS(cpu_)
                                                        , T const &a) noexcept
  {
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>)
      return false;
    else
      return is_nez(a) && (abs(a) < Smallestposval<T>());
  }
  

  
  EVE_FORCEINLINE constexpr bool is_denormal_(EVE_SUPPORTS(cpu_)
                                             , bool const &a) noexcept
  {
    return false;
  }
  
}

#endif
