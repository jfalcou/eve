//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_xor.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sinpicospi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/function/converter.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy_large.hpp>
#include <eve/module/real/special/detail/kernel_bessel_ij_small.hpp>
#include <eve/module/real/special/detail/kernel_bessel_jy.hpp>

/////////////////////////////////////////////////////////////////////////////////
// These routines are detail of the computation of cylindrical bessel functions
// of the first kind and integer orders.
// They are not meant to be called directly,  as their validities depends on
// n and x ranges values which are not tested on entry.
// The inspiration is from boost math
/////////////////////////////////////////////////////////////////////////////////
namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_large (I n, T x) noexcept
  {
    return asymptotic_bessel_j_large_x_2(T(n), x);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_forward (I n, T x, T j0, T j1) noexcept
  {
    auto prev = j0;    //cyl_bessel_j0(x);
    auto current = j1; //cyl_bessel_j1(x);
    T scale(1), value(j0);
    auto nn = if_else(n < x, n, zero);
    for (int k = 1; k < eve::maximum(nn); ++k)
    {
      auto t0 = k < nn;
      T fact = 2 * k / x;
      // rescale if we would overflow or underflow:
      auto test = (eve::abs(fact) > 1) && ((valmax(as(x)) - eve::abs(prev)) / eve::abs(fact) < eve::abs(current))&&t0;
      if (eve::any(test))
      {
        scale = if_else(test, scale/current, scale);
        prev  = if_else(test, prev/current,  prev);
        current = if_else(test, one, current);
      }
      value = if_else(t0, fms(fact, current, prev), value);
      prev  = if_else(t0, current, prev);
      current = if_else(t0, value, current);
    };
    return value/scale;
  }

  template<integral_real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_forward (I nn, T x, T j0, T j1) noexcept
  {
    if constexpr(simd_value<I>)
      return kernel_bessel_j_int_forward (convert(nn, as<element_type_t<T>>()), x, j0, j1);
    else
      return kernel_bessel_j_int_forward (T(nn), x, j0, j1);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_small (I n, T x) noexcept
  {
    return bessel_j_small_z_series(T(n), x);
  }

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_medium (I n, T x) noexcept
  {
    auto [j, jp, y, yp] = bessel_jy(T(n), x);
    return j;
  }

  /////////////////////////////////////////////////////////////////////////
  // bessel_j of integer order
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int_pos (I n, T x) noexcept
  {
    // n and x are positive here
    EVE_ASSERT(eve::all(is_flint(n)), "kernel_bessel_j_int_pos : somme n are not floating integer");
    EVE_ASSERT(eve::all(is_nltz(x)), "kernel_bessel_j_int_pos : somme x are not positive");
    EVE_ASSERT(eve::all(is_nltz(n)), "kernel_bessel_j_int_pos : somme n are not positive");
    auto j0 = cyl_bessel_j0(x);
    auto j1 = cyl_bessel_j1(x);

    auto br_large =  [](auto n,  auto x)
      {
        return kernel_bessel_j_int_large(n, x);
      };
    auto br_forward =  [j0, j1](auto n,  auto x)
      {
        return kernel_bessel_j_int_forward (n, x, j0, j1);
      };
    auto br_small =  [](auto n,  auto x)
      {
        return kernel_bessel_j_int_small(n, x);
      };
    auto br_medium =  [](auto n,  auto x)
      {
        return kernel_bessel_j_int_medium (n, x);
      };

    if constexpr(scalar_value<I> && scalar_value<T>)
    {
      if (x == inf(as(x)))                          return zero(as(x));
      if (asymptotic_bessel_large_x_limit(T(n), x)) return br_large(T(n), x);
      if (n == 0)                                   return j0;                //cyl_bessel_j0(x);
      if (n == 1)                                   return j1;                //cyl_bessel_j1(x);
      if (is_eqz(x))                                return x;                 // as n >= 2
      if (n < x)                                    return br_forward(n, x);  // forward recurrence
      if ((n > x * x / 4) || (x < 5))               return br_small(T(n), x); // serie
      return br_medium(n, x);                                                 // medium recurrence
    }
    else
    {
      using elt_t =  element_type_t<T>;
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r =  if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx, allbits, x);
      auto iseqzn = is_eqz(n);
      if (eve::any(iseqzn))
      {
        r = if_else(iseqzn, j0, r);
        x = if_else(iseqzn, allbits, x);
      }
      auto iseq1n = is_equal(n, one(as(n)));
      if (eve::any(iseq1n))
      {
        r = if_else(iseq1n, j1, r);
        x = if_else(iseq1n, allbits, x);
      }
      auto notdone = is_not_nan(x);
      auto nn = convert(n, as<elt_t>());
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_large,  notdone, asymptotic_bessel_large_x_limit(nn, x), r, nn, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_forward,  notdone, nn < x, r, nn, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_small,  notdone, (nn > x * x / 4) || (x < 5), r, nn, x);
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_medium,  notdone, r, nn, x);
            }
          }
        }
      }
      return r;
    }
  }
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto   kernel_bessel_j_int (I n, T x) noexcept
  {
    auto xlt0 = is_ltz(x);
    auto nlt0 = is_ltz(n);
    auto isoddn =  is_odd(n);
//     T factor = if_else(nlt0 && isoddn, T(-1), T(1));  // J_{-n}(z) = (-1)^n J_n(z)
//     factor *=  if_else(xlt0 && isoddn, T(-1), T(1));  // J_{n}(-z) = (-1)^n J_n(z)
    auto j = kernel_bessel_j_int_pos( eve::abs(n), eve::abs(x));
    return if_else(isoddn && logical_xor(nlt0, xlt0), -j, j);
  }


  /////////////////////////////////////////////////////////////////////////
  // bessel_j of non integer order
  template<floating_real_value T>
  EVE_FORCEINLINE auto  kernel_bessel_j_flt (T n, T x) noexcept
  {
    EVE_ASSERT(eve::none(is_flint(n)), "kernel_bessel_j_flt : some nu are floating integers");

    auto br_large =  [](auto n,  auto x)
      {
        return kernel_bessel_j_int_large(n, x);
      };

    auto br_medium =  [](auto n,  auto x)
      {
        return  kernel_bessel_j_int_medium(n, x);
      };

    if constexpr(scalar_value<T>)
    {
      if(is_ltz(x))                                 return nan(as(x));
      if (x == inf(as(x)))                          return zero(as(x));
      if (asymptotic_bessel_large_x_limit(n, x))    return br_large(n, x);
      if (is_eqz(x))                                return zero(as(x));
      return br_medium(n, x);
    }
    else
    {
      auto xlt0 = is_ltz(x);
      auto r = nan(as(x));
      auto isinfx = x == inf(as(x));
      r = if_else(isinfx, zero(as(x)), allbits);
      x = if_else(isinfx||xlt0, allbits, x);
      auto notdone = is_not_nan(x);

      if( eve::any(notdone) )
      {
        notdone = next_interval(br_large,  notdone, asymptotic_bessel_large_x_limit(n, x), r, n, x);
        if( eve::any(notdone) )
        {
          notdone = last_interval(br_medium,  notdone, r, n, x);
        }
      }
      return r;
    }
  }
}
