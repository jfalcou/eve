//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto atanh_(EVE_SUPPORTS(cpu_)
                            , const T &x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto absx = eve::abs(x);
      auto t =  absx+absx;
      auto z1 = oneminus(absx);
      auto test =  absx < half(eve::as<T>());
      auto tmp = if_else(test, absx, t)/z1;
      if   constexpr(scalar_value<T>) tmp = test ? fma(t, tmp, t) : tmp;
      else                            tmp = if_else(test, fma(t,tmp,t), tmp);
      return bit_xor(bitofsign(x), half(eve::as<T>())*log1p(tmp));
    }
    else return apply_over(atanh, x);
  }
}
