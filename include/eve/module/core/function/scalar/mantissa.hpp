//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/constant/mantissamask.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto mantissa_(EVE_SUPPORTS(cpu_),
                                           T const &a) noexcept
  requires std::floating_point<T>
  {
    if(!a) return a;
    if constexpr(eve::platform::supports_invalids)
    {
      if(is_not_finite(a)) return a;
    }
    return bit_or(bit_and(a,Mantissamask<T>()),One<T>());
  }
}

#endif
