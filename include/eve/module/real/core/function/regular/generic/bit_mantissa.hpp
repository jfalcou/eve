//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
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
      return (Mantissabits_mask<T>()&& a);
    }
    else return apply_over(bit_mantissa, a);
  }
}
