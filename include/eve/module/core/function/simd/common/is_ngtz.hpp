//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NGTZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NGTZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/zero.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/is_not_greater.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/constant/zero.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_ngtz_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
      return is_eqz(v);
    else
    {
      if constexpr(std::is_floating_point_v<T>) return is_not_greater(v, Zero(as(v)));
      if constexpr(std::is_integral_v<T>) return is_lez(v); 
    } 
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_ngtz_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return logical_not(v);
  }
}

#endif
