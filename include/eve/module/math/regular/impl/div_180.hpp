//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T div_180_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto test = is_eqz(a);
      if constexpr(scalar_value<T>)
      {
        if (test) return a;
      }
      using elt_t = element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, double>)
      {
        const T Ch = T(5.5555555555555557675773137304986448725685477256775e-3);
        const T Cl = T(2.12021758174943082362265970771770243087787985109985e-19);
        T c = Cl*a;
        return if_else(test, a, fma(a, Ch, c));
      }
      else
      {
        return float32(div_180(float64(a)));
      }
    }
    else return apply_over(div_180, a);
  }
}
