//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c)
                  noexcept requires(T, Arithmetic<T>)
  {
    if constexpr(std::is_same_v<T, float>)
      return float(double(a)*double(b)+double(c));
#ifdef  EVE_CAN_USE_FLOAT128
     else if constexpr(std::is_same_v<T, double>)
       return double(__float128(a)*__float128(b)+__float128(c));
#endif
    else
      return a * b + c;
  }
}

#endif
