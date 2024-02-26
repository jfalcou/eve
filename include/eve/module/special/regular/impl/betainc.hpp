//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/lbeta.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template< typename T0, typename T1, typename T2, callable_options O>
  constexpr EVE_FORCEINLINE
  eve::common_value_t<T0, T1> betainc_(EVE_REQUIRES(cpu_), O const&
                                     , T0 const& x, T1 const & a, T2 const & b)
  {
    if constexpr(std::same_as<T0, T1> && std::same_as<T0, T2>)
    {
      auto betacf = [](auto x, auto a, auto b)
        {
          // continued fraction for incomplete Beta function, used by betainc
          constexpr std::size_t itmax = 100;
          auto const            o     = one(as(x));
          auto                  epsi  = 10 * eps(as(x));
          auto                  fpmin = sqr(eps(as(x)));
          auto                  qab   = a + b;
          auto                  qap   = inc(a);
          auto                  qam   = dec(a);
          auto                  c     = o;
          auto                  d     = rec(maxmag(oneminus(qab * x / qap), fpmin));
          auto                  h     = d;
          for( std::size_t m = 1; m <= itmax; ++m )
          {
            T0    vm(m);
            auto vm2 = vm + vm;
            auto aa  = vm * (b - vm) * x / ((qam + vm2) * (a + vm2));
            d        = rec(maxmag(fma(aa, d, o), fpmin));
            c        = maxmag(fma(aa, rec(c), o), fpmin);
            h *= d * c;
            aa       = -(a + vm) * (qab + vm) * x / ((a + vm2) * (qap + vm2));
            d        = rec(maxmag(fma(aa, d, o), fpmin));
            c        = maxmag(fma(aa, rec(c), o), fpmin);
            auto del = d * c;
            h *= del;
            if( eve::all(eve::abs(oneminus(del)) < epsi) ) return h; // Are we done?
          }
          return h;
        };
      auto bt   = exp(fma(a, log(x), b * log1p(-x)) - lbeta(a, b));
      auto test = (x > inc(a) / (a + b + T0(2)));
      auto xx   = oneminus[test](x);
      auto aa   = if_else(test, b, a);
      auto bb   = if_else(test, a, b);
      auto res  = bt * betacf(xx, aa, bb) / aa;
      return if_else(is_ltz(xx) || xx > one(as(x)),
                     allbits,
                     if_else(is_eqz(xx), zero, if_else(x == one(as(x)), one, oneminus[test](res))));
    }
    else
    {
      return arithmetic_call(betainc, x, a, b);
    }
  }
}
