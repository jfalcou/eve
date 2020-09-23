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
#include <eve/function/modf.hpp>
#include <eve/function/converter.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pow_abs, a, b);
  }

  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    const T Oneo_16 = T(0.0625);
    //        using i_t = as_integer_t<T>;
    T ax             = eve::abs(a);
    auto [xm, ee]    = pedantic_(frexp)(ax);
    auto [x, i]      = detail::kernel_select(xm);
    T z              = sqr(x);
    T w              = detail::kernel_pow1(x, z);
    w                = fma(mhalf(eve::as<T>()), z, w);
    const T Log2_em1 = T(0.44269504088896340735992468100189);
    w                = fma(Log2_em1, w, w);
    z                = fma(Log2_em1, x, w);
    z += x;
    w          = fnma(floating_(i), Oneo_16, ee);
    auto reduc = [Oneo_16](T x) {
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
    auto    e           = int_(w);
    Wb                  = W - Wb;
    auto test           = is_gtz(Wb);
    e                   = inc[test](e);
    Wb                  = sub[test](Wb, Oneo_16);
    z                   = detail::kernel_pow2(Wb) * Wb;
    i                   = inc[is_gtz(e)](e / 16);
    e                   = fms(i, 16, e);
    w                   = detail::twomio16(e);
    z                   = fma(w, z, w);
    z                   = pedantic_(ldexp)(z, i);
    if constexpr( eve::platform::supports_infinites )
    {
      auto gtax1 = is_greater(ax, one(eve::as<T>()));
      z          = if_else(is_equal(b, inf(eve::as<T>())), if_else(gtax1, inf(eve::as<T>()), eve::zero), z);
      z          = if_else(is_equal(b, minf(eve::as<T>())), if_else(gtax1, eve::zero, inf(eve::as<T>())), z);
      z = if_else(is_equal(ax, inf(eve::as<T>())), if_else(is_gtz(b), inf(eve::as<T>()), binarize(is_gez(b))), z);
    }
    z = if_else(zer_ret, eve::zero, z);
    z = if_else(inf_ret, inf(eve::as<T>()), z);
    z = if_else(is_equal(ax, one(eve::as<T>())), ax, z);

    z = if_else(is_eqz(a), if_else(is_ltz(b), eve::inf(eve::as<T>()), binarize(is_eqz(b))), z);
    if constexpr( eve::platform::supports_invalids )
    {
      z = if_else(is_nan(a), if_else(is_eqz(b), one(eve::as<T>()), eve::allbits), z);
    }
    return z;
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto pow_abs_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  {
    const T Oneo_16 = T(0.0625);
    using i_t       = as_integer_t<T>;
    T xx            = eve::abs(a0);
    if( xx == one(eve::as<T>()) )
      return xx;
    if( is_eqz(xx) )
      return is_eqz(a1) ? one(eve::as<T>()) : is_ltz(a1) ? inf(eve::as<T>()) : zero(eve::as<T>());
    if constexpr( eve::platform::supports_infinites )
    {
      if( xx == a1 && a1 == inf(eve::as<T>()) )
        return inf(eve::as<T>());
      if( xx == inf(eve::as<T>()) && a1 == minf(eve::as<T>()) )
        return zero(eve::as<T>());
      if( a1 == inf(eve::as<T>()) )
        return (xx < one(eve::as<T>())) ? zero(eve::as<T>()) : inf(eve::as<T>());
      if( a1 == minf(eve::as<T>()) )
        return (xx > one(eve::as<T>())) ? zero(eve::as<T>()) : inf(eve::as<T>());
      if( xx == inf(eve::as<T>()) )
        return (a1 < zero(eve::as<T>())) ? zero(eve::as<T>()) : ((a1 == zero(eve::as<T>())) ? one(eve::as<T>()) : inf(eve::as<T>()));
    }
    if constexpr( eve::platform::supports_invalids )
    {
      if( is_nan(a0) )
        return is_eqz(a1) ? one(eve::as<T>()) : a0;
      if( is_nan(a1) )
        return nan(eve::as<T>());
    }
    auto [xm, e]     = pedantic_(eve::ifrexp)(xx);
    auto [x, i]      = detail::kernel_select(xm);
    T z              = sqr(x);
    T w              = detail::kernel_pow1(x, z);
    w                = fma(mhalf(eve::as<T>()), z, w);
    const T Log2_em1 = T(0.44269504088896340735992468100189);
    w                = fma(Log2_em1, w, w);
    z                = fma(Log2_em1, x, w);
    z += x;
    w          = fnma(floating_(i), Oneo_16, floating_(e));
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
    if( w > Powlargelim )
      return inf(eve::as<T>());
    if( w < Powlowlim )
      return zero(eve::as<T>());
    e  = w;
    Wb = W - Wb;    //
    if( Wb > 0.0f ) //
    {
      ++e;
      Wb -= Oneo_16; //
    }
    z = detail::kernel_pow2(Wb) * Wb; //
    i = (e / 16) + (e >= 0);
    e = fms(i, i_t(16), e);
    w = detail::twomio16(e);
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
    return eve::exp(b * eve::log(eve::abs(a)));
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic_(pow_abs), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), pedantic_type const &, T x, T y) noexcept
  {
    using i_t = as_integer_t<T, unsigned>;
    using eli_t = element_type_t<i_t>;
    eli_t const largelimit = (sizeof(eli_t) == 4 ? 31 : 63);
    auto ylt0 = y < zero(as(y));
    auto ax = eve::abs(x);
    auto [yf,  yi] = eve::modf(eve::abs(y));
//      std::cout <<" yf "<< yf << std::endl;
//      std::cout <<" yi "<< yi << std::endl;
    auto test =  yf > 0.5;
    yf = dec[test](yf);
    auto z = eve::exp(yf * eve::log(ax));
    yi = inc[test](yi);
    auto ax_is1 = ax == eve::one(as(x));
    yi = if_else(ax_is1, eve::one, yi);
    auto large = (yi > largelimit);
    yi =  if_else(large, eve::one, yi);
    auto zen = [](T base, i_t expo){
      T result(1);
      while( any(expo) )
      {
        result *= if_else(is_odd(expo), base, T(1));
        expo = shr(expo, 1);
        base = sqr(base);
      }
      return result;
    };
    auto iseqzx = is_eqz(x);
    z *= zen(ax, uint_(yi));
    z =  if_else(large, if_else(is_less(ax, one(as(x))), zero, inf(as(x))), z);
    z =  if_else(iseqzx && ylt0, zero, z);
    z =  if_else(is_infinite(ax), inf(as(x)), z);
    z =  if_else(ylt0, rec(z), z);
    z =  if_else(ax_is1 || is_eqz(y), one, z);
    z =  if_else(iseqzx && is_gtz(y), zero, z);
    return z;
  }
}
