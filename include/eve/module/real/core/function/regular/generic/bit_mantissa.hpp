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
#include <eve/function/bit_and.hpp>
#include <eve/constant/mantissa_bits.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr as_integer_t<T> bit_mantissa_(EVE_SUPPORTS(cpu_)
                                                         , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return bit_and(Mantissabits_mask<T>(), a);
    }
    else return apply_over(bit_mantissa, a);
  }
}
