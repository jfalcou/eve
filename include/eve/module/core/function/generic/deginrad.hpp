//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DEGINRAD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DEGINRAD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/fma.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T deginrad_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    auto ridh  = Ieee_constant<T, 0x3c8ef000U,  0x3f91df46a0000000ll>();
    auto ridl  = Ieee_constant<T, 0x36a35129U,  0x3de294e9c8ae0ec6ll>(); 
    return fma(a, ridl, a*ridh);
  }
}

#endif
