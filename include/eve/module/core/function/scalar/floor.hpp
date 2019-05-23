//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FLOOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FLOOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/dec.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto floor_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept requires( T, Arithmetic<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto z =  trunc(a0);
      return dec[z > a0](z);
    }
    else return a0; 
  }
}

#endif
