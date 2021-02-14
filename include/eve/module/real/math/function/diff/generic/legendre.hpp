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

#include <eve/function/legendre.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/none.hpp>
#include <eve/detail/apply_over.hpp>
// temporary measure
#include <eve/detail/diff_div.hpp>
// temporary measure

namespace eve::detail
{

  template<integral_scalar_value N, floating_value T>
  EVE_FORCEINLINE constexpr auto legendre_(EVE_SUPPORTS(cpu_)
                                          , diff_type<1> const &
                                          , N const & l
                                          , T const &x) noexcept
  {
    auto legendre_next = [](auto ll, auto x, auto pl, auto plm1)
      {
        return fms(inc(2*ll) * x,  pl, ll * plm1) / inc(ll);
      };
    T p0 = one(as(x));
    T p1 = x;
    T p_prime;
    bool odd = l & 1;
    // If the order is odd, we sum all the even polynomials:
    if (odd)
    {
      p_prime = p0;
    }
    else // Otherwise we sum the odd polynomials * (2n+1)
    {
      p_prime = 3*p1;
    }

    unsigned n = 1;
    while(n < l - 1)
    {
      std::swap(p0, p1);
      p1 = legendre_next(n, x, p0, p1);
      ++n;
      if (odd)
      {
        p_prime += (2*n+1)*p1;
        odd = false;
      }
      else
      {
        odd = true;
      }
    }
    return p_prime;
  }

  template<integral_simd_value I, floating_scalar_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_)
                                , diff_type<1> const &
                                , I nn
                                , T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return laguerre(nn, f_t(x));
  }

  template<integral_simd_value N, floating_simd_value T>
  EVE_FORCEINLINE constexpr T legendre_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , N const & l
                                       , T const &x) noexcept
  //  requires index_compatible_values<N, T>
  {
    using elt_t = element_type_t<T>;
    auto p0 = one(as(x));
    auto p1 = x;
    auto isoddl = is_odd(l);
    auto p_prime = if_else(isoddl, p0, 3*p1);
    auto ll = convert(l, as<elt_t>());
    auto nn = one(as(ll));
    auto test = nn < dec(ll);
    if (none(test)) return p_prime;
    auto legendre_next = [](auto ll, auto x, auto pl, auto plm1)
      {
        return fms(inc(2*ll) * x,  pl, ll * plm1) / inc(ll);
      };
    while(any(test))
    {
      auto p = p0;
      p1 = p0;
      p0 = p;
      p1 = legendre_next(nn, x, p0, p1);
      nn = inc[test](nn);
      p_prime = add[isoddl && test](p_prime, inc(2*nn)*p1);
      isoddl = !isoddl;
      test = nn < dec(ll);
    }
    return p_prime;
  }
}
