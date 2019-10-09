//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_NEXTAFTER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/half.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  nextafter_(EVE_SUPPORTS(cpu_), T const &x, T const &y) noexcept
  requires(T, Vectorizable<T>)
  {
    return (x < y) ? next(x) : ((y < x) ? prev(x) : x); 
  }
}

#endif
