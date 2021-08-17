//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/add.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/one.hpp>
#include <utility>

namespace eve::detail
{
  template<integral_scalar_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto hermite_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    auto p0 = one(as(x));
    if(is_eqz(n)) return p0;
    auto p1 = x+x;
    auto c = one(as(n));
    auto hermite_next = [](auto c,  auto x,  auto hn,  auto hnm1)
      {
        return 2*fms(x, hn, c*hnm1);
      };
    while(c < n)
    {
      std::swap(p0, p1);
      p1 = hermite_next(c, x, p0, p1);
      ++c;
   }
    return p1;
  }

  template<integral_scalar_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto hermite_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    T p0 = one(as(x));
    if(is_eqz(n)) return p0;
    T p1 = x+x;
    I c = one(as(n));
    auto hermite_next = [](auto n,  auto x,  auto hn,  auto hnm1)
      {
        auto z = fma(x, hn, -T(n)*hnm1);
        return z+z;
      };
    while(c < n)
    {
      std::swap(p0, p1);
      p1 = hermite_next(c, x, p0, p1);
      ++c;
    }
    return p1;
  }

  template<integral_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto hermite_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return hermite(nn, f_t(x));
  }

    template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto hermite_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    auto p0 = one(as(x));
    auto iseqzn = is_eqz(nn);
    if(eve::all(iseqzn)) return p0;
    auto p1 = add[!iseqzn](x, x);
    auto n =  convert(nn, as<elt_t>());
    auto c = one(as(n));
    auto hermite_next = [](auto c,  auto x,  auto hn,  auto hnm1)
      {
        return 2*eve::fma(x, hn, -c*hnm1);
      };
    auto test = c < n;
    auto swap = [](auto cond, auto& a, auto& b){
      auto c = a;
      a = if_else(cond, b, a);
      b = if_else(cond, c, b);
    };

    while(eve::any(test))
    {
      swap(test, p0, p1);
      p1 = if_else(test, hermite_next(c, x, p0, p1), p1);
      c = inc[test](c);
      test = c < n;
    }
    return if_else(iseqzn,  one, p1);
  }
}
