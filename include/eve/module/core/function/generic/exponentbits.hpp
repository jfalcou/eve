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
#include <eve/detail/meta.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value  T>
  EVE_FORCEINLINE  auto exponentbits_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  {
    return bit_and(Expobits_mask<T>(), a); 
  }
}

#endif
