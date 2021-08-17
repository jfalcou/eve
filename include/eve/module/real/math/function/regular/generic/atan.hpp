//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/real/math/detail/generic/atan_kernel.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

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

