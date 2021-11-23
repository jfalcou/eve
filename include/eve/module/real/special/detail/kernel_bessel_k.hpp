//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/maxlog.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twopi.hpp>
#include <eve/function/cyl_bessel_k0.hpp>
#include <eve/function/cyl_bessel_k1.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sinh.hpp>
#include <eve/module/real/special/detail/kernel_bessel_ik.hpp>
//#include <eve/module/real/special/detail/kernel_bessel_ij_small.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of modifiesd cylindrical bessel
// fnctions of the first kind.                  .
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_k_int_forward (I nn, T x, T k0, T k1) noexcept
  {
    auto prev = k0; //cyl_bessel_j0(x);
    auto current = k1; //cyl_bessel_j1(x);
    T scale(1), value(0);
    for (int k = 1; k < eve::maximum(nn); k++)
    {
      auto t0 = k < nn;
      T fact = 2 * k / x;
      // rescale if we would overflow or underflow:
      auto test = ((valmax(as(x)) - eve::abs(prev)) / eve::abs(fact) < eve::abs(current))&&t0;
      if (eve::any(test))
      {
        scale = if_else(test, scale/current, scale);
        prev  = if_else(test, prev/current,  prev);
        current = if_else(test, one, current);
      }
      value = if_else(t0, fma(fact, current, prev), value);
      prev  = if_else(t0, current, prev);
      current = if_else(t0, value, current);
    };
    return value/scale;
  }

 template<integral_real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_k_int_forward (I nn, T x, T k0, T k1) noexcept
  {
    if constexpr(simd_value<I>)
      return kernel_bessel_k_int_forward (convert(nn, as<element_type_t<T>>()), x, k0, k1);
    else
      return kernel_bessel_k_int_forward (T(nn), x, k0, k1);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_k_int_small (I n, T x) noexcept
  {
    return bessel_k_small_z_series(T(n), x);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_k_int_medium (I n, T x) noexcept
  {
    auto [i, io, k, kp] = bessel_ik(T(n), x);
    return k;
  }

  /////////////////////////////////////////////////////////////////////////
  // bessel_k of integer order
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_k_int (I n, T x) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "kernel_bessel_j_int : somme n are not floating integer");
    auto k0 = cyl_bessel_k0(x);
    auto k1 = cyl_bessel_k1(x);
    auto br_forward =  [k0, k1](auto n,  auto x)
      {
        return kernel_bessel_k_int_forward (n, x, k0, k1);
      };

    if constexpr(scalar_value<T>)
    {
      if (is_ngez(x) || is_ngez(n))                 return nan(as(x));
      if (is_eqz(x))                                return (n == 0) ? one(as(x)) : zero(as(x));
      if (x == inf(as(x)))                          return inf(as(x));
      if (n == 0)                                   return k0;               //cyl_bessel_k0(x);
      if (n == 1)                                   return k1;               //cyl_bessel_k1(x);
      return br_forward(n, x);                                               // general
    }
    else
    {
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r =  if_else(isinfx, inf(as(x)), allbits);
      x = if_else(isinfx, mone, x);
      auto iseqzx = is_eqz(x);
      auto iseqzn = is_eqz(n);
      if (eve::any(iseqzx))
      {
        r = if_else(iseqzx, if_else(iseqzn, zero, one(as(x))), r);
      }
      if (eve::any(iseqzn))
      {
        r = if_else(iseqzn, cyl_bessel_k0(x), r);
      }
      auto iseq1n = n == one(as(n));
      if (eve::any(iseq1n))
      {
        r = if_else(n == one(as(n)), cyl_bessel_k1(x), r);
      }
      auto notdone = is_gez(x) && !(iseqzn || iseq1n) ;
      x = if_else(notdone, x, allbits);
      if(eve::any(notdone)) return if_else(notdone, br_forward(n, x), r);
      else                  return r;
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto  kernel_bessel_k_flt (T n, T x) noexcept
  {
    EVE_ASSERT(eve::none(is_flint(n)), "kernel_bessel_k_flt : some nu are floating integers");

    auto br_medium =  [](auto n,  auto x)
      {
        auto [i, ip, k, kp] = kernel_bessel_ik(T(n), x);
        return k;
      };

    if constexpr(scalar_value<T>)
    {
      if(is_ngez(x)||is_ngez(n))                    return nan(as(x));
      if (x == inf(as(x)))                          return zero(as(x));
      if (is_eqz(x))                                return zero(as(x));
      return br_medium(n, x);
    }
    else
    {
      auto nneg = is_ltz(n);
      auto xlt0 = is_ltz(x);
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r = if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx||nneg||xlt0, allbits, x);
      auto notdone = is_not_nan(x);
      if(eve::any(notdone)) return if_else(notdone, br_medium(n, x), r);
      else                  return r;
    }
  }


}
