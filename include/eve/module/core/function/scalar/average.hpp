//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/half.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  average_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept requires(T, vectorizable<T>)
  {
    if constexpr(std::is_integral_v<T>) { return (a0 & a1) + ((a0 ^ a1) >> 1); }
    else
    {
      return fma(a0, Half(as(a0)), a1 * Half(as(a0)));
    }
  }
}

#endif
