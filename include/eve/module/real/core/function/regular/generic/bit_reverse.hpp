//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_reverse_(EVE_SUPPORTS(cpu_), T v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      T r = v; // r will be reversed bits of v; first get LSB of v
      int s = sizeof(v) * 8 - 1; // extra shift needed at end

      for (v >>= 1; v; v >>= 1)
      {
        r <<= 1;
        r |= v & 1;
        s--;
      }
      return r <<= s; // shift when v's highest bits are zero
    }
    else
    {
      return map(bit_reverse, v);
    }
  }

  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_reverse_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::bit_reverse, t);
  }

}
