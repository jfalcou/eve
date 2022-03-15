//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <eve/module/math/constant/minlogdenormal.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr T expm1_(EVE_SUPPORTS(cpu_), pedantic_type const &, T xx) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t       = element_type_t<T>;
      using i_t         = as_integer_t<T>;
      const T Log_2hi   = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      const T Log_2lo   = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      const T Invlog_2  = Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
      T       k         = nearest(Invlog_2 * xx);
      auto    xlelogeps = xx <= logeps(eve::as(xx));
      auto    xgemaxlog = xx >= maxlog(eve::as(xx));
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(xx) )
          return xx;
        if( xgemaxlog )
          return inf(eve::as<T>());
        if( xlelogeps )
          return mone(eve::as<T>());
      }
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T x        = fnma(k, Log_2hi, xx);
        x          = fnma(k, Log_2lo, x);
        T hx       = x * half(eve::as<T>());
        T hxs      = x * hx;
        T r1       = horn<T, 0X3F800000U, 0XBD08887FU, 0X3ACF6DB4U>(hxs);
        T t        = fnma(r1, hx, T(3));
        T e        = hxs * ((r1 - t) / (T(6) - x * t));
        e          = fms(x, e, hxs);
        i_t ik     = int_(k);
        T   two2mk = bit_cast(shl(maxexponent(eve::as<T>()) - ik, nbmantissabits(eve::as<elt_t>())), as<T>());
        k          = oneminus(two2mk) - (e - x);
        k          = D()(ldexp)(k, ik);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        T hi       = fnma(k, Log_2hi, xx);
        T lo       = k * Log_2lo;
        T x        = hi - lo;
        T hxs      = sqr(x) * half(eve::as<T>());
        T r1       = horn<T,
                    0X3FF0000000000000ULL,
                    0XBFA11111111110F4ULL,
                    0X3F5A01A019FE5585ULL,
                    0XBF14CE199EAADBB7ULL,
                    0X3ED0CFCA86E65239ULL,
                    0XBE8AFDB76E09C32DULL>(hxs);
        T t        = T(3) - r1 * half(eve::as<T>()) * x;
        T e        = hxs * ((r1 - t) / (T(6) - x * t));
        T c        = (hi - x) - lo;
        e          = (x * (e - c) - c) - hxs;
        i_t ik     = int_(k);
        T   two2mk = bit_cast(shl(maxexponent(eve::as<T>()) - ik, nbmantissabits(eve::as<T>())), as<T>());
        T   ct1    = oneminus(two2mk) - (e - x);
        T   ct2    = inc((x - (e + two2mk)));
        k          = if_else((k < T(20)), ct1, ct2);
        k          = D()(ldexp)(k, ik);
      }
      if constexpr( simd_value<T> )
      {
        k = if_else(xgemaxlog, inf(eve::as<T>()), k);
        k = if_else(is_eqz(xx), xx, k);
        k = if_else(xlelogeps, eve::mone, k);
      }
      return k;
    }
    else
      return apply_over(pedantic(expm1), xx);
  }
}
