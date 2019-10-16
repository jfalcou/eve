//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_or.hpp> 
#include <eve/constant/mantissamask.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto mantissa_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a) noexcept
  requires(wide<T, N, ABI>, floating<T>)
  {
    auto test =  is_eqz(a);
    if constexpr(eve::platform::supports_invalids)
    {
      test =  logical_or(test, is_not_finite(a));
    }
    return if_else(test, a, bitwise_or(bitwise_and(a,Mantissamask<T>()),One<T>()));
  }
}

#endif
