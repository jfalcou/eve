//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<typename  I, typename L, typename T, callable_options O>
  auto
  gegenbauer_(EVE_REQUIRES(cpu_), O const&, I n, L lambda, T x)
  {
    if constexpr(simd_value<T> != simd_value<L>)
    {
      using l_t = as_wide_as<L, T>;
      using t_t = as_wide_as<T, L>;
      if constexpr(scalar_value<I>)
      {
        l_t wl(lambda);
        t_t wt(x);
        return gegenbauer(n, wl, wt);
      }
      else if constexpr(simd_value<I>)
      {
        using wl_t = as_wide_as<l_t, I>;
        using wt_t = as_wide_as<t_t, I>;
        return gegenbauer(n, wl_t(lambda), wt_t(x));
      }
    }
    else
    {
      if constexpr(scalar_value<I>)
      {
        if( has_native_abi_v<T> )
        {
          using elt_t = element_type_t<L>;
          auto p0     = one(as(x));
          if( is_eqz(n) ) return p0;

          auto y0(p0);
          auto y1(2 * lambda * x);

          auto  yk    = y1;
          elt_t k(2);
          elt_t k_max = n * inc(eps(as(elt_t())));
          auto   gamma(2 * dec(lambda));
          auto  test = k < k_max;
          while( test )
          {
            yk = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
            y0 = y1;
            y1 = yk;
            ++k;
            test = k < k_max;
          }
          return yk;
        }
        else return apply_over(gegenbauer, n, lambda, x);
      }
      else // I simd
      {
        if( has_native_abi_v<I> )
        {
          using elt_t  = element_type_t<L>;
          auto  y0     = one(as(x));
          auto  iseqzn = is_eqz(n);
          if( eve::all(iseqzn) ) return y0;
          auto  y1 = 2 * lambda * x;

          auto  yk = y1;
          L     k(2);
          auto  k_max = convert(n, as(elt_t())) * inc(eps(as(elt_t())));
          auto  gamma = 2 * dec(lambda);
          auto  test  = k < k_max;
          while( eve::any(test) )
          {
            yk   = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
            y0   = y1;
            y1   = yk;
            k    = inc(k);
            test = k < k_max;
          }
          return if_else(iseqzn, one, yk);
        }
        else return apply_over(gegenbauer, n, lambda, x);
      }
    }
  }
}
