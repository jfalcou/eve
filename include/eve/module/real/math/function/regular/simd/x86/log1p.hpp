//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invsqrt_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/musl.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/plain.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>

namespace eve::detail
{
  // this implementation is better only if we are in avx_ without avx2_

  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto log1p_(EVE_SUPPORTS(cpu_), plain_type const &, const T &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log1p(f).c */
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
      T    Log_2hi     = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T    Log_2lo     = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      T    uf          = inc(a0);
      auto isnez       = is_nez(uf);
      auto [x, k]      = frexp(uf);
      auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      k   = dec[x_lt_sqrthf](k);
      T f = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      T c    = if_else(k >= 2, oneminus(uf - a0), a0 - dec(uf)) / uf;
      T hfsq = half(eve::as<T>()) * sqr(f);
      T s    = f / (2.0f + f);
      T z    = sqr(s);
      T w    = sqr(z);
      T t1, t2;
      if constexpr( std::is_same_v<element_type_t<T>, float> )
      {
        t1 = w * horn<T, 0x3eccce13, 0x3e789e26>(w);
        t2 = z * horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
      }
      else if constexpr(std::is_same_v<element_type_t<T>, double>)
      {
        t1 = w * horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll>(w);
        t2 = z
             * horn<T,
                    0x3fe5555555555593ll,
                    0x3fd2492494229359ll,
                    0x3fc7466496cb03dell,
                    0x3fc2f112df3e5244ll>(w);
      }
      T R = t2 + t1;
      T r = fma(k, Log_2hi, ((fma(s, (hfsq + R), k * Log_2lo + c) - hfsq) + f));
      T zz;
      if constexpr( eve::platform::supports_infinites )
      {
        zz = if_else(isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
      }
      else
      {
        zz = if_else(isnez, r, minf(eve::as<T>()));
      }
      return if_else(is_ngez(uf), eve::allbits, zz);
    }
    else
      return apply_over(plain(log1p), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation for avx
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto log1p_(EVE_SUPPORTS(avx_), wide<T, N> const &v) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr( current_api < avx2 )
      return plain(log1p)(v);
    else
      return musl_(log1p)(v);
  }
}
