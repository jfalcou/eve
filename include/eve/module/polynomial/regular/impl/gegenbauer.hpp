//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{

  template<typename I, typename T, typename U, callable_options O>
  constexpr as_wide_as_t<common_value_t<T, U>, I>
  gegenbauer_(EVE_REQUIRES(cpu_), O const&, I nn, U lambda, T x)
    requires(value<U>)
  {
    using c_t   = as_wide_as_t<common_value_t<T, U>, I>;
    using elt_t = element_type_t<c_t>;
    if constexpr(scalar_value<I>)
    {
      auto p0     = one(as(x));
      if( is_eqz(nn) ) return c_t(p0);

      c_t y0(p0);
      c_t y1(2 * lambda * x);

      auto  yk    = y1;
      elt_t k     = 2;
      elt_t k_max = nn * inc(eps(as(elt_t())));
      c_t   gamma(2 * dec(lambda));
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
    else
    {
      auto xx = c_t(x);
      if( has_native_abi_v<T> )
      {
        auto   y0     = one(as(xx));
        auto iseqzn   = is_eqz(nn);
        if( eve::all(iseqzn) ) return y0;
        auto n  = convert(nn, as(elt_t()));
        auto    y1 = 2 * lambda * xx;

        auto    yk = y1;
        elt_t   k(2);
        auto    k_max = n * inc(eps(as(elt_t())));
        auto    gamma = 2 * dec(lambda);
        auto    test  = k < k_max;
        while( eve::any(test) )
        {
          yk   = if_else(test, fms((2 + gamma / k) * xx, y1, inc(gamma / k) * y0), yk);
          y0   = y1;
          y1   = yk;
          k    = inc(k);
          test = k < k_max;
        }
        return if_else(iseqzn, one, yk);
      }
      else return apply_over(gegenbauer, nn, lambda, x);
    }
  };
}
