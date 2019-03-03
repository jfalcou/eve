//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>   
#include <eve/constant/false.hpp>
#include <cmath>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T>
  is_nan_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_integral_v<T> || eve::is_logical_v<T>)
      return False<as_logical_t<T>>();
    else
      return std::isunordered(a, a); 
  }
}

#endif
 
