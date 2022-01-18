//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/arithmetic/regular/shl.hpp>  // SUPPRESS
#include <eve/module/math/constant/math.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_eval( T const &  z) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(std::is_same_v<elt_t, float>)
    {
      T y = horn<T, 0x3d2aaaa5 , 0xbab60619 , 0x37ccf5ce> (z);
      return inc( fma(z,mhalf(eve::as<T>()), y* sqr(z)));
    }
    else if constexpr(std::is_same_v<elt_t, double>)
    {
      T y = horn<T, 0x3fe0000000000000ll, 0xbfa5555555555551ll, 0x3f56c16c16c15d47ll,
        0xbefa01a019ddbcd9ll, 0x3e927e4f8e06d9a5ll, 0xbe21eea7c1e514d4ll, 0x3da8ff831ad9b219ll > (z);
      return oneminus(y*z);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_eval( const T & z
                                         , const T & x) noexcept
  {
    // here T is float or double and x positive
    using elt_t = element_type_t<T>;
   if constexpr(std::is_same_v<elt_t, float>)
    {
      T  y1 = horn<T, 0xbe2aaaa2 , 0x3c08839d , 0xb94ca1f9> (z);
      return fma(y1*z,x,x);
    }
    else if constexpr(std::is_same_v<elt_t, double>)
    {
      T y1 = horn<T, 0xbfc5555555555548ll, 0x3f8111111110f7d0ll, 0xbf2a01a019bfdf03ll,
        0x3ec71de3567d4896ll, 0xbe5ae5e5a9291691ll, 0x3de5d8fd1fcf0ec1ll> (z);
      return fma(y1*z,x,x);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto tancot_eval( const T & z) noexcept
  {
    // here T is float or double and z positive
    T zz = eve::sqr(z);
    if constexpr(std::is_same_v<element_type_t<T>, float>)
    {
      return fma(horn<T, 0x3eaaaa6fu, 0x3e0896ddu, 0x3d5ac5c9u, 0x3cc821b5u, 0x3b4c779cu, 0x3c19c53bu>(zz), zz*z, z);
    }
    else if constexpr(std::is_same_v<element_type_t<T>, double>)
    {
      T num = horn<T,0xc1711fead3299176ull, 0x413199eca5fc9dddull, 0xc0c992d8d24f3f38ull >(zz);
      T den = horn1<T, 0xc189afe03cbe5a31ull, 0x4177d98fc2ead8efull, 0xc13427bc582abc96ull, 0x40cab8a5eeb36572ull>(zz);
      return fma(z, (zz*(num/den)), z);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_finalize(  const T & fn
                                             ,  const T & xr
                                             ,  const T & dxr = T(0)) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      using i_t =  as_integer_t<T, signed>;
      i_t n = i_t(fn);
      i_t swap_bit = n&i_t(1);
      i_t sign_bit = shl(bit_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
      T z = sqr(xr);
      T  se = sin_eval(z, xr);
      T  ce = cos_eval(z);
      z =  swap_bit ?  fma(dxr, ce, se) : fnma(se, dxr, ce);
      return bit_xor(z,sign_bit);
    }
    else
    {
      using elt_t =  element_type_t<T>;
      auto tmp =  binarize(fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), signmask(eve::as<elt_t>()));
      T z = sqr(xr);
      T se = sin_eval(z, xr);
      T ce = cos_eval(z);
      z = if_else(swap_bit, fma(dxr, ce, se), fnma(se, dxr, ce));
      return bit_xor(z, sign_bit);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sincos_finalize( T a0, T fn, T xr, T dxr = T(0)) noexcept
  {
    auto z = sqr(xr);
    auto  se0 = sin_eval(z, xr);
    auto  ce0 = cos_eval(z);
    if constexpr(scalar_value<T>)
    {
      using i_t =  as_integer_t<T, signed>;
      i_t n = int_(fn);
      i_t swap_bit = n&one(eve::as<i_t>());
      auto sin_sign_bit = bit_xor(bitofsign(a0), shl(n&i_t(2), sizeof(i_t)*8-2));
      i_t cos_sign_bit = shl(bit_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
      auto ce = fnma(se0, dxr, ce0);
      auto se = fma(dxr, ce0, se0);
      if (swap_bit) std::swap(ce, se);
      se = bit_xor(se,sin_sign_bit);
      ce = bit_xor(ce,cos_sign_bit);
      return kumi::make_tuple(se, ce);
    }
    else
    {
      using elt_t =  element_type_t<T>;
      auto tmp =  binarize(fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto cos_sign_bit = binarize(is_nez(bit_xor(swap_bit, tmp)), signmask(eve::as<elt_t>()));
      auto sin_sign_bit = bit_xor(bitofsign(a0),if_else(tmp, signmask(eve::as<T>()), eve::zero));
      auto test = is_nez(swap_bit);
      return kumi::make_tuple( bit_xor(if_else(test, ce0, se0), sin_sign_bit)
                            , bit_xor(if_else(test, se0, ce0), cos_sign_bit) );
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sin_finalize( T a0
                                             , T fn
                                             , T xr
                                             , T dxr = T(0)) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      using i_t =  as_integer_t<T, signed>;
      if (is_not_finite(xr)) return nan(eve::as<T>());
      i_t n = int_(fn);
      i_t swap_bit = n&one(eve::as<i_t>());
      auto  sign_bit = bit_xor(bitofsign(a0), shl(n&i_t(2), sizeof(i_t)*8-2));
      auto z = sqr(xr);
      auto se = sin_eval(z, xr);
      auto ce = cos_eval(z);
      xr =  swap_bit ? fnma(se, dxr, ce) : fma(dxr, ce, se);
      return bit_xor(xr,sign_bit);
    }
    else
    {
      auto tmp =  binarize(fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto sign_bit = bit_xor(bitofsign(a0), if_else(tmp, signmask(eve::as<T>()), eve::zero));
      auto z = sqr(xr);
      auto se = sin_eval(z, xr);
      auto ce = cos_eval(z);
      z = if_else(swap_bit, fnma(se, dxr, ce), fma(dxr, ce, se));
      return bit_xor(z, sign_bit);
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_finalize(T a0
                                             , T fn
                                             , T xr
                                             , T dxr = T(0)) noexcept
  {
    auto aa0lteps = eve::abs(a0) < eps(as<T>());
    T y = tancot_eval(xr);
    if constexpr(scalar_value<T>)
    {
      if (aa0lteps) return a0;
      if (is_not_finite(xr)) return nan(eve::as<T>());
      y =  (int(fn)&1) ? -rec(y): y;
      if (dxr) y+= dxr*fma(y, y, one(eve::as<T>()));
      return bit_xor(y, bitofsign(a0));
    }
    else
    {
      auto tmp = binarize( fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto test = is_eqz(swap_bit);
      y = if_else(test, y, -rec(y));
      y = fma(dxr, fma(y, y, one(eve::as<T>())), y);
      return if_else(aa0lteps, a0, bit_xor(y, bitofsign(a0)));
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto cot_finalize(T a0
                                             , T fn
                                             , T xr
                                             , T dxr = T(0)) noexcept
  {
    T y = tancot_eval(xr);
    if constexpr(scalar_value<T>)
    {
      if (is_not_finite(a0)) return nan(eve::as<T>());
      y =  (int(fn)&1) ? -y: rec(y);
      if (dxr) y+= dxr*fma(y, y, one(eve::as<T>()));
      return bit_xor(y, bitofsign(a0));
    }
    else
    {
      auto aa0lteps = eve::abs(a0) < eps(as<T>());
      auto tmp = binarize( fn >= T(2));
      auto swap_bit = (fma(T(-2), tmp, fn));
      auto test = is_eqz(swap_bit);
      y = if_else(test,rec(y),-y);
      y = fma(dxr, fma(y, y, one(eve::as<T>())), y);
      return if_else(aa0lteps, /*pedantic*/(rec)(a0), bit_xor(y, bitofsign(a0)));
    }
  }
}
