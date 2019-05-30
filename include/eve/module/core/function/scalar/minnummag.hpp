//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MINNUMMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MINNUMMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/minmag.hpp>
#include <type_traits>


namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T minnummag_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
      if (is_nan(a0)) return a1;
    return minmag(a0, a1);
  }
}

#endif
