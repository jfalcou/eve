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

#include <eve/concept/value.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/lgamma.hpp>
#include <type_traits>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE auto anp_(EVE_SUPPORTS(cpu_), T n, T p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto r = nan(as(n));
      auto notdone = is_gez(n)&&is_gez(p)&&is_flint(n)&&is_flint(p);
      if (any(notdone))
      {
        r = if_else( notdone, if_else(n >=  p, nearest(exp(lgamma(n+1)-lgamma(n-p+1))), zero), r);
      }
      return r;
    }
    else
      return apply_over(anp, n, p);
  }
}
