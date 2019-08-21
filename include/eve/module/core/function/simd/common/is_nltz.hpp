//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NLTZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NLTZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/zero.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/constant/true.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_nltz_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
     if constexpr(std::is_unsigned_v<T>)
       return True(as(v));
    else
    {
      if constexpr(std::is_floating_point_v<T>) return is_not_less(v, Zero(as(v)));
      if constexpr(std::is_integral_v<T>) return is_gez(v); 
    }  
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_nltz_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return True(as(v));
  }
}

#endif
