//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <type_traits>
#include <eve/platform.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto expx2_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(expx2, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T expx2_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(eve::platform::supports_invalids && scalar_value<T>)
      {
        if (is_nan(a0)) return a0;
      }
      if constexpr(scalar_value<T> && eve::platform::supports_infinites)
        if (is_infinite(a0)) return inf(as<T>());
      T x =  eve::abs(a0);
       const T Expx2c1 = Ieee_constant<T, 0x42000000U, 0x4060000000000000ull>();
       const T Expx2c2 = Ieee_constant<T, 0x3d000000U, 0x3f80000000000000ull>();
       /* Represent x as an exact multiple of 1/32 plus a residual.  */
       T m = Expx2c1 * eve::floor(fma(Expx2c2, x, half(as<T>())));
       x -= m;
       /* x**2 = m**2 + 2mf + f**2 */
       T u = sqr(m);
       T u1 = fma(T(2) * m, x, sqr(x));
       /* u is exact, u1 is small.  */
       auto gtmxlg = is_not_less_equal(u+u1, maxlog(as<T>()));
       if constexpr(scalar_value<T>)
       {
         if (gtmxlg) return inf(as<T>());
         return eve::exp(u)*eve::exp(u1);
       }
      else if  constexpr(simd_value<T>)
      {
        T r = eve::if_else(gtmxlg,eve::inf(as<T>()), eve::exp(u)*eve::exp(u1));
        if constexpr(eve::platform::supports_infinites)
          r =  eve::if_else((x == inf(as<T>())), x, r);
        if constexpr(eve::platform::supports_invalids)
          r =  eve::if_else(is_nan(a0), eve::allbits, r);
        return r;
      }
      return u+u1;
    }
    else
      return apply_over(expx2, a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T expx2_(EVE_SUPPORTS(cpu_), T a0,  T s) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(eve::platform::supports_invalids && scalar_value<T>)
      {
        if (is_nan(a0)) return a0;
      }
      T sgn =  signnz(s);
      T x =  abs(a0)*sgn;
      const T Expx2c1 = Ieee_constant<T, 0x42000000U, 0x4060000000000000ull>();
      const T Expx2c2 = Ieee_constant<T, 0x3d000000U, 0x3f80000000000000ull>();
      // Represent x as an exact multiple of 1/32 plus a residual.
      T m = Expx2c1*eve::floor(fma(Expx2c2, x, eve::half(as<T>())));
      T f =  sub[is_finite(x)](x, m);
      // x**2 = m**2 + 2mf + f**2
      T u = sgn*eve::sqr(m);
      T u1 = sgn*fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      auto gtmxlg = is_not_less_equal(abs(u+u1), eve::maxlog(as<T>()));
      if constexpr(scalar_value<T>)
      {
        if (gtmxlg) return sgn > 0 ? inf(as<T>()) : zero(as<T>());
        return exp(u)*exp(u1);
      }
      else if  constexpr(simd_value<T>)
      {
        auto valinf = if_else(sgn > 0, inf(as<T>()), eve::zero);
        T r = eve::if_else(gtmxlg, valinf, eve::exp(u)*eve::exp(u1));
        if constexpr(eve::platform::supports_infinites)
          r =  eve::if_else(x == inf(as<T>()), x, r);
        if constexpr(eve::platform::supports_invalids)
          r =  eve::if_else(is_nan(a0), eve::allbits, r);
        return r;
      }
    }
    else
      return apply_over(expx2, a0, s);
  }
}
