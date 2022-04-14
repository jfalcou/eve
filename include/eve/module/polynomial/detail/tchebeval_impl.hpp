//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/range.hpp>
#include <concepts>
#include <iterator>
#include <initializer_list>

namespace eve::detail
{
  //================================================================================================
  //== Tchebeval with range
  //================================================================================================
  template<decorator D, value T0, std::ranges::bidirectional_range R>
  EVE_FORCEINLINE constexpr common_compatible_t<T0, typename R::value_type>
  tchebeval_impl(D const & d, T0 xx, R const & r) noexcept
  {
    using r_t = common_compatible_t<T0, typename R::value_type>;
    auto x =  r_t(xx);
    auto first =  std::begin(r);
    auto cur  =  std::end(r);
    if (first == cur) return r_t(0);
    if (std::distance(first, cur) == 1) return r_t((*first)/2);
    else
    {
      --cur;
      auto dfma = d(fma);
      r_t b2 = zero(as<r_t>());
      r_t b1 = r_t(*cur--);
      for(; cur != first; --cur)
      {
        r_t tmp = dfma(x+x, b1, *cur-b2);
        b2 = b1;
        b1 = tmp;
      }
      return dfma(x, b1, fms(*cur, half(as<r_t>()), b2));
    }
  }

  template<decorator D, value T0, value T1, value T2, std::ranges::bidirectional_range R>
  EVE_FORCEINLINE constexpr common_compatible_t<T0, typename R::value_type>
  tchebeval_impl(D const & d, T0 xx, T1 a, T2 b, R const & r) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, typename R::value_type>;
    auto x =  r_t(xx);
    auto first =  std::begin(r);
    auto cur  =  std::end(r);
    auto den = rec(b-a);
    if (first == cur) return r_t(0);
    if (std::distance(first, cur) == 1) return r_t((*first)/2);
    else
    {
      auto dfma = d(fma);
      auto up = [&dfma, &r, first](auto ,  auto t)
        {
          auto cur  = std::end(r);
          --cur;
          r_t b2(0);
          r_t b1(*cur--);
          for(; cur != first; --cur)
          {
            r_t tmp = dfma(t+t, b1, *cur- b2);
            b2 = b1;
            b1 = tmp;
          }
          return dfma(t, b1, fms(*cur, half(as<r_t>()), b2));
        };

      auto downg = [&dfma, &r, first](auto u,  auto t)
        {
          auto cur  = std::end(r);
          --cur;
          r_t b(*cur--);
          r_t d(b);
          r_t b2(0);
          for(; cur != first; --cur)
          {
            d = dfma(u+u, b, *cur+ d);
            b2 = b;
            b = d+b;
          }
           return dfma(t, b, fms(*cur, half(as<r_t>()), b2));
        };

      auto downl = [&dfma, &r, first](auto u,  auto t)
        {
          auto cur  = std::end(r);
          --cur;
          r_t b(*cur--);
          r_t d(b);
          r_t b2(0);
          for(; cur != first; --cur)
          {
            d = dfma(u+u, b, *cur- d);
            b2 = b;
            b = d-b;
          }
          return dfma(t, b, fms(*cur, half(as<r_t>()), b2));
        };

      auto compute_lesser = [&up, &downl, &den, &a](auto x)
        {
          auto u = 2*(x-a)*den;
          auto t = dec(u);
          auto tc = t > r_t(-0.6);;
          if (eve::all(tc)) return up(u, t);
          else if (eve::none(tc))   return downl(u, t);
          else return if_else(tc, up(u, t), downl(u, t));
        };

      auto compute_greater = [&up, &downg, &den, &b](auto x)
        {
          auto u = -2*(b-x)*den;
          auto t = inc(u);
          auto tc = t < r_t(0.6);;
          if (eve::all(tc)) return up(u, t);
          else if (eve::none(tc))   return downg(u, t);
          else return if_else(tc, up(u, t), downg(u, t));
        };
      auto test = (x-a) < (b-x);
      if (eve::all(test)) return compute_lesser(x);
      else if (eve::none(test))   return compute_greater(x);
      else return if_else(test, compute_lesser(x), compute_greater(x));
    }
  }


  //================================================================================================
  //== N+1 parameters
  //================================================================================================

  template<decorator D, value T0, value ...Cs>
  EVE_FORCEINLINE constexpr
  common_compatible_t<T0, Cs...>
  tchebeval_impl(D const & d, T0 x, Cs... cs) noexcept
  {
    constexpr size_t N = sizeof...(cs);
    //copy the coefficients to an array
    if constexpr (N == 0) return zero(as(x));
    else
    {
      using r_t = common_compatible_t<T0, Cs...>;
      std::array<r_t, N> c{r_t(cs)...};
      return tchebeval_impl(d, r_t(x), c);
    }
  }
}
