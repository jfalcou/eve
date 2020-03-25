//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/raw.hpp>
#include <type_traits>
#include <cmath>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  sqrt_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a0) noexcept Requires(T, Vectorizable<T>)
  {
    return eve::sqrt(a0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sqrt_(EVE_SUPPORTS(cpu_),
                                       T const &a0) noexcept Requires(T, Vectorizable<T>)
  {
    if(std::is_integral_v<T>)
    {
      return T(::sqrt(double(a0)));
    }
    else
    {
      if constexpr(std::is_same_v<T, float>) return std::sqrt(a0);
      if constexpr(std::is_same_v<T, double>) return ::sqrt(a0);
    }
  }
}

#endif
