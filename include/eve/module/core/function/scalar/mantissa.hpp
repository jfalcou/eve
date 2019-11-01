//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MANTISSA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MANTISSA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/constant/mantissamask.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto mantissa_(EVE_SUPPORTS(cpu_),
                                           T const &a) noexcept
  requires(T, floating_point<T>)
  {
    if(!a) return a;
    if constexpr(eve::platform::supports_invalids)
    {
      if(is_not_finite(a)) return a;
    }
    return bitwise_or(bitwise_and(a,Mantissamask<T>()),One<T>());
  }
}

#endif
