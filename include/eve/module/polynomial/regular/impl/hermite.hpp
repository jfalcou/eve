//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <iostream>

namespace eve::detail
{
  //Recurrence relation for hermite polynomials:
  template<value N, floating_value T, callable_options O> //successor
  EVE_FORCEINLINE auto
  hermite_(EVE_REQUIRES(cpu_), O const&, N n, T x, T hn, T hnm1) noexcept
  {
    auto z = fms(x, hn, T(n) * hnm1);
    return z + z;
  }

  template<scalar_value I, scalar_value T, callable_options O>
  EVE_FORCEINLINE auto
  hermite_(EVE_REQUIRES(cpu_), O const&, I n, T x)
  {
//    std::cout << "scalar scalar" << std::endl;
      auto p0 = one(as(x));
      if( is_eqz(n) ) return p0;
      auto p1 = x + x;
      auto c  = one(as(n));
      while( c < n )
      {
        std::swap(p0, p1);
        p1 = hermite[successor](c, x, p0, p1);
        ++c;
      }
      return p1;
  }

 template<scalar_value I, simd_value T, callable_options O>
  EVE_FORCEINLINE auto
  hermite_(EVE_REQUIRES(cpu_), O const&, I n, T x)
  {
//    std::cout << "scalar simd" << std::endl;
    if constexpr( has_native_abi_v<T> )
    {
      T p0 = one(as(x));
      if( is_eqz(n) ) return p0;
      T p1 = x + x;
      I c  = one(as(n));

 //      auto succ = [](auto n, auto x, auto hn, auto hnm1)
//         {
//           auto z = fms(x, hn, T(n) * hnm1);
//           return z + z;
//         };
      while( c < n )
      {
        std::swap(p0, p1);
        p1 = hermite[successor](c, x, p0, p1);
        ++c;
      }
      return p1;
    }
    else return apply_over(hermite, n, x);
  }

  template<integral_simd_value I, scalar_value T, callable_options O>
  auto //EVE_FORCEINLINE as_wide_t<T, I>
  hermite_(EVE_REQUIRES(cpu_), O const&, I nn, T x)
  requires(scalar_value<T>)
  {
    using f_t =  wide<T, cardinal_t<I>>; //as_wide_as_t<T, I>;
    return hermite(nn, f_t(x));
  }

  template<simd_value I, simd_value T, callable_options O>
  auto //EVE_FORCEINLINE as_wide_t<T, I>
  hermite_(EVE_REQUIRES(cpu_), O const&, I nn, T x)
  {
//    std::cout << "simd simd" << std::endl;
    using elt_t = element_type_t<T>;
    auto p0     = one(as(x));
    auto iseqzn = is_eqz(nn);
    if( eve::all(iseqzn) ) return p0;
    auto p1   = add[!iseqzn](x, x);
    auto n    = convert(nn, as<elt_t>());
    auto c    = one(as(n));
    auto test = c < n;
    auto swap = [](auto cond, auto& a, auto& b) { // TODO Conditionnal swap with shuffles
      auto c = a;
      a      = if_else(cond, b, a);
      b      = if_else(cond, c, b);
    };

    auto succ = [](auto n, auto x, auto hn, auto hnm1)
      {
        auto z = fms(x, hn, T(n) * hnm1);
        return z + z;
      };

    while( eve::any(test) )
    {
      swap(test, p0, p1);
      p1   = if_else(test, /*hermite[successor]*/succ(c, x, p0, p1), p1);
      c    = inc[test](c);
      test = c < n;
    }
    return if_else(iseqzn, one, p1);
  }

  template<int N, floating_value T, callable_options O>
  auto //EVE_FORCEINLINE T
  hermite_(EVE_REQUIRES(cpu_), O const&, std::integral_constant<int, N> const&, T x) noexcept
  {
    if constexpr( N < 0 ) return zero(as(x));
    else if constexpr( N == 0 ) return one(as(x));
    else if constexpr( N == 1 ) return x + x;
    else if constexpr( N == 2 ) return dec(sqr(x)) * 2;
    else if constexpr( N == 3 ) return 4 * x * (sqr(x) - 3);
    else if constexpr( N == 4 )
    {
      auto x2 = sqr(x + x);
      return fnma(T(12), dec(x2), sqr(x2));
    }
    else return hermite(N, x);
  }
}
