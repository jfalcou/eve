//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EXPONENTBITS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EXPONENTBITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/function/shl.hpp>
#include <eve/platform.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/detail/meta.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE  auto exponentbits_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  requires(as_integer_t<T>, behave_as<floating_point,T>)
  {
    return bit_and(Expobits_mask<T>(), a); 
  }
}

#endif
