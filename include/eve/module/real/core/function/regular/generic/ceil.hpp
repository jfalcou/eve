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

#include <eve/detail/implementation.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T ceil_(EVE_SUPPORTS(cpu_)
                                   , T const &a0) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      T z = eve::trunc(a0);
      return inc[ z < a0 ](z);
    }
    else return apply_over(ceil, a0);
  }
}
