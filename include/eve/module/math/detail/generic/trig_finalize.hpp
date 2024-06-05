//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>


namespace eve
{

  namespace detail
  {
    template<floating_ordered_value T>
    EVE_FORCEINLINE constexpr auto
    cos_eval(T const& z) noexcept
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T y =
          eve::reverse_horner(z, T(0x1.55554ap-5f), T(-0x1.6c0c32p-10f), T(0x1.99eb9cp-16f))
          ;
        return inc(fma(z, mhalf(eve::as<T>()), y * sqr(z)));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        T y =
        eve::reverse_horner(z, T(0x1.0000000000000p-1), T(-0x1.5555555555551p-5), T(0x1.6c16c16c15d47p-10)
                           , T(-0x1.a01a019ddbcd9p-16), T(0x1.27e4f8e06d9a5p-22)
                           , T(-0x1.1eea7c1e514d4p-29), T(0x1.8ff831ad9b219p-37));
        return oneminus(y * z);
      }
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE constexpr auto
    sin_eval(const T& z, const T& x) noexcept
    {
      // here T is float or double and x positive
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T y1 =
          eve::reverse_horner(z, T(-0x1.555544p-3f), T(0x1.11073ap-7f), T(-0x1.9943f2p-13f))
          ;
        return fma(y1 * z, x, x);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        T y1 =
        eve::reverse_horner(z, T(-0x1.5555555555548p-3), T(0x1.111111110f7d0p-7), T(-0x1.a01a019bfdf03p-13)
                           , T(0x1.71de3567d4896p-19), T(-0x1.ae5e5a9291691p-26), T(0x1.5d8fd1fcf0ec1p-33));
        return fma(y1 * z, x, x);
      }
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE constexpr auto
    tancot_eval(const T& z) noexcept
    {
      // here T is float or double and z positive
      T zz = eve::sqr(z);
      if constexpr( std::is_same_v<element_type_t<T>, float> )
      {
        return fma(eve::reverse_horner(zz, T(0x1.5554dep-2f), T(0x1.112dbap-3f), T(0x1.b58b92p-5f)
                                      , T(0x1.90436ap-6f), T(0x1.98ef38p-9f), T(0x1.338a76p-7f)),zz*z,z);
      }
      else if constexpr( std::is_same_v<element_type_t<T>, double> )
      {
        T num =
          eve::reverse_horner(zz, T(-0x1.11fead3299176p+24), T(0x1.199eca5fc9dddp+20), T(-0x1.992d8d24f3f38p+13))
          ;
        T den =
          eve::reverse_horner(zz, T(-0x1.9afe03cbe5a31p+25), T(0x1.7d98fc2ead8efp+24)
                             , T(-0x1.427bc582abc96p+20), T(0x1.ab8a5eeb36572p+13), T(0x1.0p0));
        return fma(z, (zz * (num / den)), z);
      }
    }


    template<floating_ordered_value T>
    EVE_FORCEINLINE constexpr auto
    cos_finalize(const T& fn, const T& xr, const T& dxr = T(0)) noexcept
    {
      auto tmp      = one[fn >= T(2)](eve::as(xr));
      auto swap_bit = (eve::fma(T(-2), tmp, fn));
      auto zz1 = eve::is_odd(fn+tmp);
      auto sign    =  eve::if_else(zz1, eve::mone(eve::as(xr)), eve::one(eve::as(xr)));
      T    z        = eve::sqr(xr);
      T    se       = sin_eval(z, xr);
      T    ce       = cos_eval(z);
      z             = eve::if_else(swap_bit, eve::fma(dxr, ce, se), eve::fnma(se, dxr, ce));
      return sign*z;
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE auto
    sincos_finalize(T a0, const T& fn, const T& xr, const T& dxr = T(0)) noexcept
    {
      auto tmp          = one[fn >= T(2)](eve::as(xr));
      auto swap         = eve::is_nez(eve::fma(T(-2), tmp, fn));
      auto cos_sign     = eve::if_else(eve::is_odd(fn+tmp), eve::mone(eve::as(xr)), eve::one(eve::as(xr)));
      auto sin_sign     =  eve::signnz(a0);
      sin_sign *= eve::if_else(tmp, eve::mone(eve::as(a0)), eve::one(eve::as(a0)));
      auto z            = sqr(xr);
      auto se0          = sin_eval(z, xr);
      auto ce0          = cos_eval(z);
      auto ce           = fnma(se0, dxr, ce0);
      auto se           = fma(dxr, ce0, se0);
      return kumi::make_tuple((if_else(swap, ce, se)*sin_sign)
                             , if_else(swap, se, ce)*cos_sign);
    }

    template<ordered_value T>
    EVE_FORCEINLINE constexpr auto
    sin_finalize(T a0,  T fn,  T xr, T dxr = T(0)) noexcept
    {
      auto tmp      = one[fn >= T(2)](eve::as(xr));
      auto swap_bit = (eve::fma(T(-2), tmp, fn));
      auto sign = eve::signnz(a0);
      sign *= eve::if_else(tmp, eve::mone(eve::as(a0)), eve::one(eve::as(a0)));
      auto z        = eve::sqr(xr);
      auto se       = sin_eval(z, xr);
      auto ce       = cos_eval(z);
      z             =  eve::if_else(swap_bit,  eve::fnma(se, dxr, ce),  eve::fma(dxr, ce, se));
      return sign*z;
    }

    template<typename T>
    EVE_FORCEINLINE constexpr auto
    tan_finalize(T a0, T fn, T xr, T dxr = T(0)) noexcept
    {
      auto aa0lteps = eve::abs(a0) < eps(as<T>());
      T    y        = tancot_eval(xr);
      if constexpr( scalar_value<T> )
      {
        if( aa0lteps ) return a0;
        if( is_not_finite(xr) ) return nan(eve::as<T>());
        y = (int(fn) & 1) ? -rec[pedantic2](y) : y;
        if( dxr ) y += dxr * fma(y, y, one(eve::as<T>()));
        return bit_xor(y, bitofsign(a0));
      }
      else
      {
        auto tmp      = one[fn >= T(2)](eve::as(xr));
        auto swap_bit = (fma(T(-2), tmp, fn));
        auto test     = is_eqz(swap_bit);
        y             = if_else(test, y, -rec[pedantic2](y));
        y             = fma(dxr, fma(y, y, one(eve::as<T>())), y);
        return if_else(aa0lteps, a0, bit_xor(y, bitofsign(a0)));
      }
    }

    template<typename T>
    EVE_FORCEINLINE constexpr auto
    cot_finalize(T a0, T fn, T xr, T dxr = T(0)) noexcept
    {
      T y = tancot_eval(xr);
      if constexpr( scalar_value<T> )
      {
        if( is_not_finite(a0) ) return nan(eve::as<T>());
        y = (int(fn) & 1) ? -y : rec[pedantic2](y);
        if( dxr ) y += dxr * fma(y, y, one(eve::as<T>()));
        return bit_xor(y, bitofsign(a0));
      }
      else
      {
        auto aa0lteps = eve::abs(a0) < eps(as<T>());
        auto tmp      = one[fn >= T(2)](eve::as(xr));
        auto swap_bit = (fma(T(-2), tmp, fn));
        auto test     = is_eqz(swap_bit);
        y             = if_else(test, rec[pedantic2](y), -y);
        y             = fma(dxr, fma(y, y, one(eve::as<T>())), y);
        return if_else(aa0lteps, rec[pedantic2](a0), bit_xor(y, bitofsign(a0)));
      }
    }
  }
}
