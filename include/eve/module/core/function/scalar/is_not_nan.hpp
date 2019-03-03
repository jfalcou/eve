//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_NAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_NAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr logical<T> is_not_nan_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
      return a == a;
    else
      return true;
  }
}

#endif

