//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/cyl_bessel_y0.hpp>
#include <eve/function/cyl_bessel_y1.hpp>
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
  EVE_FORCEINLINE auto cyl_bessel_y_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  {
    if( in == 0 )  return cyl_bessel_y0(x);
    else  if( in == 1 )  return cyl_bessel_y1(x);
    else return cyl_bessel_y(T(in), x);
  }

  template<integral_scalar_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_y_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  {
    if( in == 0 )  return cyl_bessel_y0(x);
    else  if( in == 1 )  return cyl_bessel_y1(x);
    else return cyl_bessel_y(T(in), x);
  }

  template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto cyl_bessel_y_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    using elt_t =  element_type_t<T>;
    return cyl_bessel_y(convert(in, as<elt_t>()), x);
  }

  template<floating_real_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto cyl_bessel_y_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    if constexpr( has_native_abi_v<T> )
    {
      return cyl_bessel_y(in, I(x));
    }
    else
      return apply_over(cyl_bessel_y, in, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto cyl_bessel_y_(EVE_SUPPORTS(cpu_), T a0, T a1) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto sgn = if_else(is_ltz(a0), cospi(a0), one);
      a0 = eve::abs(a0);
      auto isneza1 =  is_nez(a1);
      auto notdone = is_nlez(a1) && is_flint(a0);
      T r = if_else(isneza1, allbits, minf(as(a1)));
      if (eve::any(notdone))
      {
        auto y0 = cyl_bessel_y0(a1);
        auto br_0 =  [](auto y0) { return y0;};
        notdone = next_interval(br_0, notdone, is_eqz(a0), r, y0);
        if (eve::any(notdone))
        {
          auto y1 = cyl_bessel_y1(a1);
          auto br_1 =  [](auto y1) { return y1;};
          notdone = next_interval(br_1, notdone, a0 == 1, r, y1);
          if (eve::any(notdone))
          {
            auto br_last = [](auto n1,  auto x,  auto y0, auto y1)
              {
                T anm2 = y0;
                T anm1 = y1;
                T r = T(2);
                T xinv = rec(x);
                T an(0);
                auto test = true_(as(x));
                do
                {
                  an = if_else(test,r*anm1*xinv-anm2, an);
                  anm2 = if_else(test,anm1, anm2);
                  anm1 = if_else(test,an, anm1);
                  r += T(2);
                  test = (r < n1);
                }
                while(eve::any(test) );
                return an;
              };
            last_interval(br_last, notdone, r, 2*abs(a0), a1, y0, y1);
          }
        }
      }
      return if_else(a1 == inf(as(a1)), zero, sgn*r);
    }
    else
      return apply_over(cyl_bessel_y, a0, a1);
  }
}
