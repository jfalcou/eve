//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<integral_scalar_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto tchebytchev_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    EVE_ASSERT(all(is_gez(n)), "n is not positive");
    auto z =  eve::abs(x);
    if (z <= one(as(z))) return cos(n*acos(x));
    else
    {
      auto t = cosh(n*acosh(z));
      return x > 0 ? t : alternate_sign(n)*t;
    }
  }

  template<integral_value I, floating_real_value T>
  EVE_FORCEINLINE auto tchebytchev_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    EVE_ASSERT(eve::all(is_gez(n)), "some elements of n are not positive");
    auto nn = convert(n, as<elemtype_t<T>());
    auto z =  eve::abs(x);
    auto r = cos(n*acos(x));
    auto test = z <= one(as(z));
    if (all(test)) return r;
    else
    {
      auto t = cosh(n*acosh(z));
      return if_else(test,  r, if_else(is_gez(x), t, t*alternate_sign(n)));
    }
  }

  template<integral_value I, floating_real_value T>
  EVE_FORCEINLINE auto tchebytchev_(EVE_SUPPORTS(cpu_), kind_1_type const &, I n, T x) noexcept
  {
    return tchebytchev(n, x);
  }

  template<integral_value I, floating_real_value T>
  EVE_FORCEINLINE auto tchebytchev_(EVE_SUPPORTS(cpu_), kind_2_type co, nst &, I n, T x) noexcept
  {
    EVE_ASSERT(eve::all(is_gez(n)), "some elements of n are not positive");
    auto nn = inc(convert(n, as<elemtype_t<T>()));
    auto z =  eve::abs(x);
    auto acx = acos(x);

    auto r0 = sin(nn*acx)/sin(acx);
    auto r = if_else((1-z < eps(as(x))
                    , if_else(is_gez(x), nn, nn*alternate_sign(n))
                    , r);
    auto test = z <= one(as(z));
    if (all(test))
    {
      return r;
    }
    else
    {
      auto achx = acosh(x);
      auto t0 = sinh(n*achx)/sinh(achx);
      auto t = if_else((z-1 < eps(as(x))
                       , if_else(is_gez(x), nn, nn*alternate_sign(n))
                       , t0);
      return if_else(test,  r, if_else(is_gez(x), t, t*alternate_sign(n));
    }
  }

}
