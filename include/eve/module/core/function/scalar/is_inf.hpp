//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <eve/constant/inf.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>
#include <iostream>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr logical<T> is_inf_(EVE_SUPPORTS(cpu_), T const& a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      puts("YO");
      std::cout << eve::abs(a) << "\n";
      std::cout << Inf<T>() << "\n";
      std::cout << (eve::abs(a) == Inf<T>()) << "\n";
      return eve::abs(a) == Inf<T>();
    }
    else
      return false;
  }
}

#endif
