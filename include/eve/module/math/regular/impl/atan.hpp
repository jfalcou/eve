//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve::detail
{
  template<floating_value T>
  EVE_FORCEINLINE auto atan_(EVE_SUPPORTS(cpu_)
                            , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      T x  = eve::abs(a);
      return bit_xor(atan_kernel(x, rec(x)), bitofsign(a));
    }
    else return apply_over(atan, a);
  }
}
