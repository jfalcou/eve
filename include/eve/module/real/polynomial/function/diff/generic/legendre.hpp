//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/legendre.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/none.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <utility>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_scalar_value N, floating_value T>
  EVE_FORCEINLINE constexpr auto legendre_(EVE_SUPPORTS(cpu_)
                                          , diff_type<1> const &
                                          , N const & l
                                          , T const &x) noexcept
  {
    if (is_eqz(l)) return T(0);
    auto legendre_next = [](auto ll, auto x, auto pl, auto plm1)
      {
        auto llp1 = inc(ll);
        return fms((llp1+ll) * x,  pl, ll * plm1) / llp1;
      };
    T p0 = one(as(x));
    T p1 = x;
    T p_prime;
    bool odd = l & one(as(l));
    p_prime = odd ? p0 : 3*p1;
    auto n = one(as(l));
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
    return if_else(eve::abs(x) > one(as(x)), allbits,  p_prime);
  }

  template<integral_simd_value I, floating_scalar_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_)
                                , diff_type<1> const &
                                , I nn
                                , T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return if_else(eve::abs(x) > one(as(x)), nan(as<f_t>()), diff(legendre)(nn, f_t(x)));
  }

  template<integral_simd_value N, floating_simd_value T>
  EVE_FORCEINLINE constexpr T legendre_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , N const & l
                                       , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    using elt_t = element_type_t<T>;
    auto p0 = one(as(x));
    auto p1 = x;
    auto isoddl = is_odd(l);
    auto p_prime = if_else(isoddl, p0, 3*p1);
    auto ll = convert(l, as<elt_t>());
    auto nn = one(as(ll));
    auto test = nn < dec(ll);
    auto legendre_next = [](auto ll, auto x, auto pl, auto plm1)
      {
        return fms(inc(2*ll) * x,  pl, ll * plm1) / inc(ll);
      };
    auto swap = [](auto cond, auto& a, auto& b){
      auto c = a;
      a = if_else(cond, b, a);
      b = if_else(cond, c, b);
    };
    while(eve::any(test))
    {
      swap(test, p0, p1);
      p1 = legendre_next(nn, x, p0, p1);
      nn = inc[test](nn);
      p_prime = add[isoddl && test](p_prime, inc(2*nn)*p1);
      isoddl = !isoddl;
      test = nn < dec(ll);
    }
    p_prime = if_else(is_eqz(l), zero, p_prime);
    return if_else(eve::abs(x) > one(as(x)), allbits, p_prime);
  }
}
