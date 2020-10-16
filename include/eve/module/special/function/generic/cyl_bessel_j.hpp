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
#include <eve/function/fms.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_nlez.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/true.hpp>
#include <type_traits>

namespace eve::detail
{
  template<integral_scalar_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto cyl_bessel_j_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  {
    if( in == 0 )  return cyl_bessel_j0(x);
    else  if( in < 0 == 1 )  return cyl_bessel_j1(x);
    else return cyl_bessel_j(T(in), x);
  }

  template<integral_scalar_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_j_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  {
    if( in == 0 )  return cyl_bessel_j0(x);
    else  if( in < 0 == 1 )  return cyl_bessel_j1(x);
    else return cyl_bessel_j(T(in), x);
  }

  template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_j_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    using elt_t =  element_type_t<T>;
    return cyl_bessel_j(convert(in, as<elt_t>()), x);
  }

  template<floating_real_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto cyl_bessel_j_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    if constexpr( has_native_abi_v<T> )
    {
      return cyl_bessel_j(in, I(x));
    }
    else
      return apply_over(cyl_bessel_j, in, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto cyl_bessel_j_(EVE_SUPPORTS(cpu_), T a0, T a1) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto sgn = if_else(is_ltz(a0), cospi(a0), one);
      a0 = eve::abs(a0);
      auto isneza1 =  is_nez(a1);
      auto notdone = (!is_odd(a0) || is_nltz(a1)) && is_flint(a0) && isneza1;
      T r = if_else(isneza1, nan(as(a1)), zero);
      if (any(notdone))
      {
        auto j0 = cyl_bessel_j0(a1);
        auto br_0 =  [](auto j0) { return j0;};
        notdone = next_interval(br_0, notdone, is_eqz(a0), r, j0);
        if (any(notdone))
        {
          auto j1 = cyl_bessel_j1(a1);
          auto br_1 =  [](auto j1) { return j1;};
          notdone = next_interval(br_1, notdone, a0 == 1, r, j1);
          if (any(notdone))
          {
            auto br_2 =  [](auto a1, auto j0,  auto j1)
              {
                return fms(T(2)*j1, rec(a1), j0);
              };
            notdone = next_interval(br_2, notdone, a0 == 2, r, a1, j0, j1);
            if (any(notdone))
            {
              auto br_last = [](auto a0,  auto a1,  auto j0, auto j1)
                {
                  std::int32_t k0 = 24;
                  auto pk = 2*(a0 + k0);
                  auto ans = pk;
                  auto xk = sqr(a1);
                  do {
                    pk  = pk - T(2);
                    ans = fnma(xk, rec(ans), pk);
                  }
                  while( --k0 > 0 );
                  /* backward recurrence */

                  pk = T(1);
                  /*pkm1 = 1.0/ans;*/
                  auto xinv = rec(a1);
                  auto pkm1 = ans * xinv;
                  auto k = dec(a0);
                  auto r = 2.0*k;
                  auto test(true_(as(a1)));
                  do{
                    auto pkm2 = (pkm1*r -  pk * a1) * xinv;
                    pk   = if_else(test, pkm1, pk);
                    pkm1 = if_else(test, pkm2, pkm1);
                    r = r-T(2);
                    k = dec(k);
                  }
                  while( any(is_gtz(k)) );
                  return if_else(abs(pk) > pkm1, j1/pk, j0/pkm1);
                };
              last_interval(br_last, notdone, r, a0, a1, j0, j1);
            }
          }
        }
      }
      return sgn*r;
    }
    else
      return apply_over(cyl_bessel_j, a0, a1);
  }
}
