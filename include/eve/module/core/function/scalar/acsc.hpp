//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ACSC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ACSC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/asin.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto acsc_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return eve::asin(rec(a0));  
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::acsc scalar ] - type is not an IEEEValue"); 
    }      
  }

}

#endif
