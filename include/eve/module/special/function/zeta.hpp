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

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/log.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/max.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/sub.hpp>
#include <eve/detail/hz_device.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE T zeta_(EVE_SUPPORTS(cpu_)
                              , T x
                              , U y) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(zeta, x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T zeta_(EVE_SUPPORTS(cpu_)
                              , T s) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      //
      // This is algorithm 3 from:
      //
      // "An Efficient Algorithm for the Riemann Zeta Function", P. Borwein,
      // Canadian Mathematical Society, Conference Proceedings.
      // See: http://www.cecm.sfu.ca/personal/pborwein/PAPERS/P155.pdf
      //
      auto sc = onceminus(s);
      const int n = if_else(sizeof(elt_t>() == 8, 18, 7);
      T sum(0);
      T two_n = ldexp(T(1), n);
      T ej_sign(one(as(s)));
      for(int j = 0; j < n; ++j)
      {
        sum += ej_sign * -two_n*pow(T(j + 1), -s);
        ej_sign = -ej_sign;
      }
      T ej_sum(one(as(s)));
      T ej_term(one(as(s)));
      for(int j = n; j <= 2 * n - 1; ++j)
      {
        sum += ej_sign * (ej_sum - two_n) * pow(T(j + 1), -s);
        ej_sign = -ej_sign;
        ej_term *= 2 * n - j;
        ej_term /= j - n + 1;
        ej_sum += ej_term;
      }
      auto powm1 = [](auto x,  auto y) // x >  0
        {
          return dec(pow(x, y));
        } ;
      return -sum / (two_n * (-powm1(T(2), sc)));
    }
    else
      return apply_over(zeta, x, y);
  }
}
