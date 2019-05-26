//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/bitwise_and.hpp>
#include <eve/function/scalar/bitwise_xor.hpp>
#include <eve/function/scalar/fma.hpp>
#include <eve/function/scalar/shr.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto average_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  requires(T, Arithmetic<T>)
  {
    if constexpr(std::is_integral_v<T>)
      return bitwise_and(a0, a1)+shr(bitwise_xor(a0, a1),1);
    else
      return fma(a0,Half(as(a0)),a1*Half(as(a0)));
  }
}

#endif
