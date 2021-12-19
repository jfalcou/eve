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
#include <eve/function/copysign.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE  auto coth_(EVE_SUPPORTS(cpu_)
                             , const T &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto x = eve::abs(a0+a0);
      auto t = rec(expm1(x));
      auto r = fma(T(2), t, T(1));
      return copysign(r, a0);
    }
    else return apply_over(coth, a0);
  }
}

