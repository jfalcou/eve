//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/max.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/detail/hz_device.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE auto ellint_rf_(EVE_SUPPORTS(cpu_)
                              , T x
                              , U y
                              , V z) noexcept
  requires compatible_values<T, U> &&  compatible_values<V, U>
  {
    return arithmetic_call(ellint_rf, x, y, z);
  }

  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE auto ellint_rf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , T x
                              , U y
                              , V z) noexcept
  requires compatible_values<T, U> &&  compatible_values<V, U>
  {
    return arithmetic_call(raw(ellint_rf), x, y, z);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_rf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , T x
                              , T y
                              , T z) noexcept
  requires has_native_abi_v<T>
  {
    T xn = x;
    T yn = y;
    T zn = z;
    T an = (x + y + z) / 3;
    T a0 = an;
    auto epsi =  pow_abs(3*eps(as(element_type_t<T>())), -1/T(8));
    T q = epsi * (eve::max)((eve::max)(eve::abs(an - xn), eve::abs(an - yn)), eve::abs(an - zn));
    T fn = one(as(x));


    // duplication
    unsigned k = 1;
    T hf = half(as(x));
    for(; k < 30; ++k)
    {
      T root_x = eve::sqrt(xn);
      T root_y = eve::sqrt(yn);
      T root_z = eve::sqrt(zn);
      T lambda = root_x * root_y + root_x * root_z + root_y * root_z;
      an = average(an, lambda) *hf;
      xn = average(xn, lambda) *hf;
      yn = average(yn, lambda) *hf;
      zn = average(zn, lambda) *hf;
      q *= T(0.25);
      fn *= T(4);
      if(eve::all(q < eve::abs(an))) break;
    }
    T denom = rec(an * fn);
    T xx = (a0 - x) * denom;
    T yy = (a0 - y) * denom;
    T zz = -xx - yy;

    // Taylor series expansion to the 7th order
    T p =  xx * yy;
    T e2 = fnma(zz, zz, p);
    T e3 = p * zz;
    // TODO put constant values in expansion
    using elt_t = element_type_t<T>;
    constexpr elt_t c0 = sizeof(elt_t) == 4 ? 1/14.0f : 1/14.0;
    constexpr elt_t c1 = sizeof(elt_t) == 4 ? 3/104.0f :3/104.0;
    constexpr elt_t c2 = sizeof(elt_t) == 4 ? -1/10.0f :-1/10.0;
    constexpr elt_t c4 = sizeof(elt_t) == 4 ? 1/24.0f  :1/24.0;
    constexpr elt_t c5 = sizeof(elt_t) == 4 ? -3/44.0f  :-3/44.0;
    constexpr elt_t c6 = sizeof(elt_t) == 4 ? -5/208.0f  :-5/208.0;
    constexpr elt_t c7 = sizeof(elt_t) == 4 ? -1/16.0f :1/16.0;
    return (fma(e3,  fma(e3, c1, c0), fma(e2, (c2 + e3*c5 + e2*(c4 + e2*c6 + e3*c7)), one(as(x))))) * rsqrt(an);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_rf_(EVE_SUPPORTS(cpu_)
                              , T x
                              , T y
                              , T z) noexcept
  requires has_native_abi_v<T>
  {
    auto r = nan(as(x));
    auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z) && is_nez(x + y) && is_nez( y + z) && is_nez(z + x);
    // any parameter nan or less than zero or more than one parameter zero implies nan
    auto br0 = [x, y, z](){return raw(ellint_rf)(x, y, z);};
    last_interval(br0, notdone, r);
    return r;
  }
}
