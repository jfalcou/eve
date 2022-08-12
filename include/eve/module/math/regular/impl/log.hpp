//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
/*EVE_FORCEINLINE */ constexpr T
log_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    T Log_2hi   = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
    T Log_2lo   = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
    using uiT   = as_integer_t<T, unsigned>;
    using iT    = as_integer_t<T, signed>;
    using elt_t = element_type_t<T>;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_logf.c */
      /*
       * ====================================================
       * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
       *
       * Developed at SunPro, a Sun Microsystems, Inc. business.
       * Permission to use, copy, modify, and distribute this
       * software is freely granted, provided that this notice
       * is preserved.
       * ====================================================
       */
      T          x = a0;
      iT         k(0);
      auto       isnez = is_nez(a0);
      logical<T> test;
      if constexpr( eve::platform::supports_denormals )
      {
        test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
        if( eve::any(test) )
        {
          k = sub[test](k, iT(23));
          x = if_else(test, x * T(8388608ul), x);
        }
      }
      uiT ix = bit_cast(x, as<uiT>());
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      ix += 0x3f800000 - 0x3f3504f3;
      k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
      ix     = (ix & 0x007fffff) + 0x3f3504f3;
      x      = bit_cast(ix, as<T>());
      T f    = dec(x);
      T s    = f / (2.0f + f);
      T z    = sqr(s);
      T w    = sqr(z);
      T t1   = w * horn<T, 0x3eccce13u, 0x3e789e26u>(w);
      T t2   = z * horn<T, 0x3f2aaaaau, 0x3e91e9eeu>(w);
      T R    = t2 + t1;
      T hfsq = half(eve::as<T>()) * sqr(f);

      T dk = float32(k);
      T r  = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
      T zz;
      if constexpr( eve::platform::supports_infinites )
      {
        zz = if_else(
            isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
      }
      else { zz = if_else(isnez, r, minf(eve::as<T>())); }
      return if_else(is_ngez(a0), eve::allbits, zz);
    }
    else // if constexpr(std::is_same_v<elt_t, double>)
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_logf.c */
      /*
       * ====================================================
       * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
       *
       * Developed at SunPro, a Sun Microsystems, Inc. business.
       * Permission to use, copy, modify, and distribute this
       * software is freely granted, provided that this notice
       * is preserved.
       * ====================================================
       */
      T          x = a0;
      iT         k(0);
      auto       isnez = is_nez(a0);
      logical<T> test;
      if constexpr( eve::platform::supports_denormals )
      {
        test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
        if( eve::any(test) )
        {
          k = sub[test](k, iT(54));
          x = if_else(test, x * T(18014398509481984ull), x);
        }
      }
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      uiT hx = bit_cast(x, as<uiT>()) >> 32;
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
      hx = (bit_and(hx, 0x000fffffull)) + 0x3fe6a09e;
      x  = bit_cast(hx << 32 | (bit_and(bit_cast(x, as<uiT>()), 0xffffffffull)), as<T>());

      T f  = dec(x);
      T s  = f / (2.0f + f);
      T z  = sqr(s);
      T w  = sqr(z);
      T t1 = w * horn<T, 0x3fd999999997fa04ull, 0x3fcc71c51d8e78afull, 0x3fc39a09d078c69full>(w);
      T t2 = z
             * horn<T,
                    0x3fe5555555555593ull,
                    0x3fd2492494229359ull,
                    0x3fc7466496cb03deull,
                    0x3fc2f112df3e5244ull>(w);
      T R    = t2 + t1;
      T hfsq = half(eve::as<T>()) * sqr(f);

      T dk = float64(k);
      T r  = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
      T zz;
      if constexpr( eve::platform::supports_infinites )
      {
        zz = if_else(
            isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
      }
      else { zz = if_else(isnez, r, minf(eve::as<T>())); }
      return if_else(is_ngez(a0), eve::allbits, zz);
    }
  }
  else return apply_over(D()(log), a0);
}

template<floating_real_scalar_value T>
/*EVE_FORCEINLINE*/ constexpr auto
log_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  using uiT = as_integer_t<T, unsigned>;
  using iT  = as_integer_t<T, signed>;
  T Log_2hi = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
  T Log_2lo = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
  if constexpr( std::is_same_v<T, float> )
  {
    /* origin: FreeBSD /usr/src/lib/msun/src/e_logf.c */
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunPro, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
    uiT ix = bit_cast(x, as<uiT>());
    iT  k  = 0;
    if( ix < 0x00800000 || ix >> 31 ) /* x < 2**-126  */
    {
      if( ix << 1 == 0 ) return minf(eve::as<T>()); /* log(+-0)=-inf */
      if( ix >> 31 ) return nan(eve::as<T>());      /* log(-#) = NaN */
      if constexpr( eve::platform::supports_denormals )
      { /* subnormal number, scale up x */
        k -= 25;
        x *= 33554432.0f;
        ix = bit_cast(x, as<iT>());
      }
    }
    else if( ix >= 0x7f800000 ) { return x; }
    else if( ix == 0x3f800000 ) return zero(eve::as(x));

    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    ix += 0x3f800000 - 0x3f3504f3;
    k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
    ix     = (ix & 0x007fffff) + 0x3f3504f3;
    x      = bit_cast(ix, as<T>());
    T f    = dec(x);
    T s    = f / (2.0f + f);
    T z    = sqr(s);
    T w    = sqr(z);
    T t1   = w * horn<T, 0x3eccce13, 0x3e789e26>(w);
    T t2   = z * horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
    T R    = t2 + t1;
    T hfsq = 0.5f * sqr(f);
    T dk   = float32(k);
    return fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
  }
  else if constexpr( std::is_same_v<T, double> )
  {
    /* origin: FreeBSD /usr/src/lib/msun/src/e_log.c */
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunSoft, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
    uiT hx = bit_cast(x, as<uiT>()) >> 32;
    iT  k  = 0;
    if( hx < 0x00100000 || hx >> 31 )
    {
      if( is_eqz(x) ) return minf(eve::as<T>()); /* log(+-0)=-inf */
      if( hx >> 31 ) return nan(eve::as<T>());   /* log(-#) = NaN */
      /* subnormal number, scale x up */
      if constexpr( eve::platform::supports_denormals )
      {
        k -= 54;
        x *= 18014398509481984.0;
        hx = bit_cast(x, as<uiT>()) >> 32;
      }
    }
    else if( hx >= 0x7ff00000 ) { return x; }
    else if( x == one(eve::as<T>()) ) return zero(eve::as<T>());
    /* reduce x into [sqrt(2)/2, sqrt(2)] */
    hx += 0x3ff00000 - 0x3fe6a09e;
    k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
    hx  = (hx & 0x000fffff) + 0x3fe6a09e;
    x   = bit_cast((uint64_t)hx << 32 | (bit_and(0xffffffffull, bit_cast(x, as<uiT>()))), as<T>());
    T f = dec(x);
    T hfsq = 0.5 * sqr(f);
    T s    = f / (2.0f + f);
    T z    = sqr(s);
    T w    = sqr(z);
    T t1   = w * horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll>(w);
    T t2   = z
           * horn<T,
                  0x3fe5555555555593ll,
                  0x3fd2492494229359ll,
                  0x3fc7466496cb03dell,
                  0x3fc2f112df3e5244ll>(w);
    T R  = t2 + t1;
    T dk = float64(k);
    return fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
  }
}

template<floating_real_value T>
/*EVE_FORCEINLINE*/ constexpr T
log_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return log(regular_type {}, x);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
log_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::log, t);
}
}
