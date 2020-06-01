//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_and.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto bitofsign_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>) return bit_and(a, Signmask(as(a)));
    else                              return apply_over(bitofsign, a);
  }
}

