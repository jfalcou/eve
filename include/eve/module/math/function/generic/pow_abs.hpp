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

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/math/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  /*EVE_FORCEINLINE */ auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pow_abs, a, b);
  }

  template<floating_real_simd_value T>
  /*EVE_FORCEINLINE */auto pow_abs_(EVE_SUPPORTS(cpu_), T a, T b) noexcept
  {
//     auto std_pow = [](auto a,  auto b){return std::pow(abs(a), b); };
//     return map(std_pow, a, b);
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t =  element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto tmp = convert(raw_(pow_abs)(convert(a, double_), convert(b, double_)), single_);
        tmp =  if_else(is_eqz(b)||is_equal(a, One(as(a))), eve::one_, tmp);
        tmp =  if_else(is_eqz(b)&&is_eqz(a), eve::one_, tmp);
        tmp =  if_else(is_equal(a, One(as(a))), eve::one_, tmp);
        return tmp;
      }
      else
      {
        const T Oneo_16 = T(0.0625);
        //        using i_t = as_integer_t<T>;
        T ax             = eve::abs(a);
        auto [xm, ee]    = pedantic_(frexp)(ax);
        auto [x, i]      = kernel_select(xm);
        T z              = sqr(x);
        T w              = kernel_pow1(x, z);
        w                = fma(Mhalf<T>(), z, w);
        const T Log2_em1 = T(0.44269504088896340735992468100189);
        w                = fma(Log2_em1, w, w);
        z                = fma(Log2_em1, x, w);
        z += x;
        w          = fnma(tofloat(i), Oneo_16, ee);
        auto reduc = [Oneo_16](T const & x) {
          // Find a multiple of 1/16 that is within 1/16 of x.
          return Oneo_16 * floor(T(16) * x);
        };
        T ya = reduc(b);
        T yb = b - ya;
        T W  = fma(z, b, w * yb);
        T Wa = reduc(W);
        T Wb = W - Wa;
        W    = fma(w, ya, Wa);
        Wa   = reduc(W);
        T u  = W - Wa;
        W    = Wb + u;
        Wb   = reduc(W);
        w    = T(16) * (Wa + Wb);
        // Test the power of 2 for over/underflow
        const T Powlargelim = Ieee_constant<T, 0x44ffe000U, 0x40cfff8000000000ULL>();
        const T Powlowlim   = Ieee_constant<T, 0xc5160000U, 0xc0d0c7c000000000ULL>();
        auto    inf_ret     = is_greater(w, Powlargelim);
        auto    zer_ret     = is_less(w, Powlowlim);
        auto    e           = toint(w);
        Wb                  = W - Wb;
        auto test           = is_gtz(Wb);
        e                   = inc[test](e);
        Wb                  = sub[test](Wb, Oneo_16);
        z                   = kernel_pow2(Wb) * Wb;
        i                   = inc[is_gtz(e)](e / 16);
        e                   = fms(i, 16, e);
        w                   = twomio16(e);
        z                   = fma(w, z, w);
        z                   = pedantic_(ldexp)(z, i);
        if constexpr( eve::platform::supports_infinites )
        {
          auto gtax1 = is_greater(ax, One<T>());
          z          = if_else(is_equal(b, Inf<T>()), if_else(gtax1, Inf<T>(), eve::zero_), z);
          z          = if_else(is_equal(b, Minf<T>()), if_else(gtax1, eve::zero_, Inf<T>()), z);
          z = if_else(is_equal(ax, Inf<T>()), if_else(is_gtz(b), Inf<T>(), binarize(is_gez(b))), z);
        }
        z = if_else(zer_ret, eve::zero_, z);
        z = if_else(inf_ret, Inf<T>(), z);
        z = if_else(is_equal(ax, One<T>()), ax, z);

        z = if_else(is_eqz(a), if_else(is_ltz(b), eve::Inf<T>(), binarize(is_eqz(b))), z);
        if constexpr( eve::platform::supports_invalids )
        {
          z = if_else(is_nan(a), if_else(is_eqz(b), One<T>(), eve::allbits_), z);
        }
        return z;
      }
    }
    else
      return apply_over(pow_abs, a, b);
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  {
    const T Oneo_16 = T(0.0625);
    using i_t       = as_integer_t<T>;
    T xx            = eve::abs(a0);
    if( xx == One<T>() )
      return xx;
    if( is_eqz(xx) )
      return is_eqz(a1) ? One<T>() : is_ltz(a1) ? Inf<T>() : Zero<T>();
    if constexpr( eve::platform::supports_infinites )
    {
      if( xx == a1 && a1 == Inf<T>() )           return Inf<T>();
      if( xx == Inf<T>() && a1 == Minf<T>() )    return Zero<T>();
      if( a1 == Inf<T>() )                       return (xx < One<T>()) ? Zero<T>() : Inf<T>();
      if( a1 == Minf<T>() )                      return (xx > One<T>()) ? Zero<T>() : Inf<T>();
      if( xx == Inf<T>() )                       return (a1 < Zero<T>()) ? Zero<T>() : ((a1 == Zero<T>()) ? One<T>() : Inf<T>());
    }
    if constexpr( eve::platform::supports_invalids )
    {
      if( is_nan(a0) ) return is_eqz(a1) ? One<T>() : a0;
      if( is_nan(a1) ) return Nan<T>();
    }
    auto [xm, e]     = pedantic_(eve::ifrexp)(xx);
    auto [x, i]      = kernel_select(xm);
    T z              = sqr(x);
    T w              = kernel_pow1(x, z);
    w                = fma(Mhalf<T>(), z, w);
    const T Log2_em1 = T(0.44269504088896340735992468100189);
    w                = fma(Log2_em1, w, w);
    z                = fma(Log2_em1, x, w);
    z += x;
    w          = fnma(tofloat(i), Oneo_16, tofloat(e));
    auto reduc = [](T x) {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return T(0.0625) * floor(T(16) * x);
    };
    T ya = reduc(a1);
    T yb = a1 - ya;
    T W  = fma(z, a1, w * yb);
    T Wa = reduc(W);
    T Wb = W - Wa;
    W    = fma(w, ya, Wa);
    Wa   = reduc(W);
    T u  = W - Wa;
    W    = Wb + u;
    Wb   = reduc(W);
    w    = T(16) * (Wa + Wb);

    // Test the power of 2 for overflow
    const T Powlargelim = Ieee_constant<T, 0x44ffe000U, 0x40cfff8000000000ULL>();
    const T Powlowlim   = Ieee_constant<T, 0xc5160000U, 0xc0d0c7c000000000ULL>();
    if( w > Powlargelim ) return Inf<T>();
    if( w < Powlowlim )   return Zero<T>();
    e  = w;
    Wb = W - Wb;    //
    if( Wb > 0.0f ) //
    {
      ++e;
      Wb -= Oneo_16; //
    }
    z = kernel_pow2(Wb) * Wb; //
    i = (e / 16) + (e >= 0);
    e = fms(i, i_t(16), e);
    w = twomio16(e);
    z = fma(w, z, w);
    z = pedantic_(ldexp)(z, i);
    return z;
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(raw_(pow_abs), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return eve::exp(b * eve::log(eve::abs(a)));
    }
    else
      return apply_over(raw_(pow_abs), a, b);
  }

}
