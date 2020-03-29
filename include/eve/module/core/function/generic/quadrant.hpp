//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_QUADRANT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_QUADRANT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/floor.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T quadrant_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(floating_value<T>) 
      {
        T b = a*T(0.25);
        return (b-floor(b))*T(4);
      }
      else if constexpr(integral_value<T>)
        return bit_and(a, T(3));
    }
    else
      return apply_over(quadrant, a); 
  }
}

#endif
