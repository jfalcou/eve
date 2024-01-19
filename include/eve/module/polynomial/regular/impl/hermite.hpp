//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  //Recurrence relation for hermite polynomials:
  template<value N, floating_value T, callable_options O> //successor
  constexpr EVE_FORCEINLINE as_wide_as_t<T, N>
  hermite_(EVE_REQUIRES(cpu_), O const&, N n, T x, T hn, T hnm1)
  {
    auto z = fms(x, hn, T(n) * hnm1);
    return z + z;
  }

  template<typename I, typename T, callable_options O>
  constexpr as_wide_as_t<T, I>
  hermite_(EVE_REQUIRES(cpu_), O const&, I n, T x)
  {
    if constexpr(scalar_value<I>)
    {
      if constexpr( has_native_abi_v<T> )
      {
        T p0 = one(as(x));
        if( is_eqz(n) ) return p0;
        T p1 = x + x;
        I c  = one(as(n));
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
    else if constexpr(simd_value<I>)
    {
      if constexpr(scalar_value<T>)
      {
        using f_t =  wide<T, cardinal_t<I>>; //as_wide_as_t<T, I>;
        return hermite(n, f_t(x));
      }
      else if constexpr(simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        auto p0     = one(as(x));
        auto iseqzn = is_eqz(n);
        if( eve::all(iseqzn) ) return p0;
        auto p1   = add[!iseqzn](x, x);
        auto nn    = convert(n, as<elt_t>());
        auto c    = one(as(nn));
        auto test = c < nn;
        while( eve::any(test) )
        {
          eve::swap_if(test, p0, p1);
          p1   = if_else(test, hermite[successor](c, x, p0, p1), p1);
          c    = inc[test](c);
          test = c < nn;
        }
        return if_else(iseqzn, one, p1);
      }
    }
  }

  template<int N, floating_value T, callable_options O>
  constexpr T hermite_(EVE_REQUIRES(cpu_), O const&, std::integral_constant<int, N> const&, T x)
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
