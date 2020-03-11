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
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/frac.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
 //  int4 n = v.i[LOW_HALF] & 3; improve quadrant ?
namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T quadrant_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    using v_t = value_type_t<T>; 
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi>)
    {
      return map(eve::quadrant, a);
    }
    else if constexpr(is_aggregated_v<t_abi>)
    {
      return aggregate(eve::quadrant, a);
    }
    else
    {
      if constexpr(std::is_floating_point_v<v_t>)
      {
        T b = a*T(0.25);
        return (b-floor(b))*T(4);
//        return frac(b)*4; 
      }
      else return bit_and(a, T(3));
    }
  }
}

#endif
