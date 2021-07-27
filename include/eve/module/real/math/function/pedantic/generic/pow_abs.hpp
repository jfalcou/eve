//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once


#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/pedantic/frexp.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/real/math/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <eve/function/modf.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/pedantic.hpp>

#include <concepts>

namespace eve::detail
{
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_), pedantic_type const &,
                               T const &a, T const &b) noexcept
  requires(has_native_abi_v<T>)
  {
    const T Oneo_16 = T(0.0625);
    using i_t = as_integer_t<T>;
    T ax             = eve::abs(a);
    auto [xm, ee]    = pedantic(frexp)(ax);
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
    auto    inf_ret     = (w > Powlargelim);
    auto    zer_ret     = (w < Powlowlim);
    auto    e           = int_(w);
    Wb                  = W - Wb;
    auto test           = is_gtz(Wb);
    e                   = inc[test](e);
    Wb                  = sub[test](Wb, Oneo_16);
    z                   = detail::kernel_pow2(Wb) * Wb;
    i                   = inc[is_gtz(e)](e / 16);
    e                   = fms(i, i_t(16), e);
    w                   = detail::twomio16(e);
    z                   = fma(w, z, w);
    z                   = pedantic(ldexp)(z, i);
    if constexpr( eve::platform::supports_infinites )
    {
      auto gtax1 = (ax > one(eve::as<T>()));
      z          = if_else(b == inf(eve::as<T>()), if_else(gtax1, inf(eve::as<T>()), eve::zero), z);
      z          = if_else(b == minf(eve::as<T>()), if_else(gtax1, eve::zero, inf(eve::as<T>())), z);
      z = if_else(ax == inf(eve::as<T>()), if_else(is_gtz(b), inf(eve::as<T>()), binarize(is_gez(b))), z);
    }
    z = if_else(zer_ret, eve::zero, z);
    z = if_else(inf_ret, inf(eve::as<T>()), z);
    z = if_else(ax ==  one(eve::as<T>()), ax, z);

    z = if_else(is_eqz(a), if_else(is_ltz(b), eve::inf(eve::as<T>()), binarize(is_eqz(b))), z);
    if constexpr( eve::platform::supports_invalids )
    {
      z = if_else(is_nan(a), if_else(is_eqz(b), one(eve::as<T>()), eve::allbits), z);
    }
    return z;
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto pow_abs_(EVE_SUPPORTS(cpu_), pedantic_type const &,
                                          T const &a0, T const &a1) noexcept
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
    auto [xm, e]     = pedantic(eve::ifrexp)(xx);
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
    z = pedantic(ldexp)(z, i);
    return z;
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(pow_abs), a, b);
  }
}
