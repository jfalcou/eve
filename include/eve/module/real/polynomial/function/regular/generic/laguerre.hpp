//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
#include <eve/function/oneminus.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/successor.hpp>
#include <utility>

namespace eve::detail
{

  // Recurrence relation for Laguerre polynomials:
  template <real_value N, floating_value T>
  EVE_FORCEINLINE T laguerre_(EVE_SUPPORTS(cpu_), successor_type const &
                                     , N n, T x, T Ln, T Lnm1) noexcept
  {
    auto np1= inc(n);
    return fms(np1 + n - x, Ln, n * Lnm1) / np1;
  }

  template<integral_scalar_value I, floating_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    auto p0 = one(as(x));
    if(is_eqz(n)) return p0;
    auto p1 = oneminus(x);
    auto vc = one(as(x));
    auto c = one(as(n));
    while(c < n)
    {
      auto p = p0;
      p0 = p1;
      auto vcp1 = inc(vc);
      p1 = successor(laguerre)(c, x, p0, p);
      vc = vcp1;
      ++c;
    }
    return p1;
  }

  template<integral_simd_value I, floating_scalar_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return laguerre(nn, f_t(x));
  }

  template<integral_simd_value I, floating_simd_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
   if (has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto p0 = one(as(x));
      auto iseqzn = is_eqz(nn);
      if(eve::all(iseqzn)) return p0;

      auto p1 = oneminus(x);
      auto n =  convert(nn, as<elt_t>());
      auto c = one(as(n));
      auto test = c < n;
      while(eve::any(test))
      {
        auto p = p0;
        p0 = p1;
        p1 =  if_else(test, successor(laguerre)(c, x, p0, p), p1);
        c =  inc(c);
        test = c < n;
      }
      return  if_else(iseqzn,  one, p1);
    }
    else
      return apply_over(laguerre, nn, x);
  }

  // Recurrence relation for Laguerre associated polynomials:
  template <real_value N, integral_value L, floating_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), successor_type const &
                                 , N n, L l, T x, T pl, T plm1) noexcept
  {
    auto np1 =  inc(n);
    auto npl =  n+l;
    return ((np1+ npl - x)*pl - npl*plm1) / np1;
  }

  // associated laguerre polynomials
  template<integral_scalar_value M, integral_scalar_value N, floating_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), N n, M m, T x) noexcept
  {
    // Special cases:
    if(m == 0) return laguerre(n, x);
    auto p0 = one(as(x));
    if(n == 0)  return p0;
    auto p1 = inc(m) - x;

    unsigned c = 1;
    while(c < n)
    {
      std::swap(p0, p1);
      p1 = successor(laguerre)(c, m, x, p0, p1);
      ++c;
    }
    return p1;
  }

  template<integral_simd_value M, integral_simd_value N, floating_scalar_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), N nn,  M mm, T x) noexcept
  {
   if (has_native_abi_v<T>)
    {
      auto iseqzm = is_eqz(mm);
      if(eve::all(iseqzm)) [[unlikely]]
      {
        return laguerre(nn, x);
      }
      else [[likely]]
      {
        using elt_t = element_type_t<T>;
        auto p0 = one(as(x));
        auto iseqzn = is_eqz(nn);
        if(eve::all(iseqzn)) [[unlikely]]
        {
          return p0;
        }
        else [[likely]]
        {
          auto m =  convert(mm, as<elt_t>());
          auto p1 = inc(m) - x;

          auto n =  convert(nn, as<elt_t>());
          auto c = one(as(n));;
          auto test = c < n;
          while(eve::any(test))
          {
            auto p = p0;
            p0 = p1;
            p1 = if_else(test, successor(laguerre)(c, m, x, p0, p), p1);
            c = inc(c);
            test = c < n;
          }
          return  if_else(iseqzn, one, if_else(iseqzm,  laguerre(n, x), p1));
        }
      }
    }
    else
      return apply_over(laguerre, nn, mm, x);
  }
}
