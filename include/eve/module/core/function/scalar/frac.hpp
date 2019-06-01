//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FRAC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FRAC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto frac_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept requires( T, Arithmetic<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return a0-trunc(a0); 
    else
      return Zero(as(a0)); 
  }
}

#endif
