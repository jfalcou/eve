//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/add.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/double_factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/p_kind.hpp>
#include <eve/function/q_kind.hpp>
#include <eve/function/successor.hpp>
#include <utility>

namespace eve::detail
{
  // basic legendre (legendre_p)
  template<real_value I, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    return p_kind(legendre)(n, x);
  }

  // Recurrence relation for legendre polynomials of all kinds
  template <real_value L, floating_value T>
  EVE_FORCEINLINE T legendre_(EVE_SUPPORTS(cpu_), successor_type const &
                             , L l, T x, T pl, T plm1) noexcept
  {
    auto lp1= inc(l);
    return fms((lp1 + l) * x, pl, l * plm1)/ lp1;
  }

  // decorated p_kind, q_kind,  scalar index:
  template<decorator Kind, integral_scalar_value I, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const &
                                , I n, T x) noexcept
  {
    auto out_of_range = eve::abs(x) > one(as(x));
    if (n < 0) n = -n-1;  //reflection formula
    auto p0 = one(as(x));
    auto p1 = x;
    if constexpr(std::same_as<Kind, p_kind_type>)
    {
      if(is_eqz(n)) return if_else(out_of_range, allbits, p0);
    }
    else if constexpr(std::same_as<Kind, q_kind_type>)
    {
      p0 = eve::atanh(x);
      if(is_eqz(n)) return if_else(out_of_range, allbits, p0);
      p1 = fms(x, p0, one(as(x)));
    }
    auto c = one(as(n));
    while(c < n)
    {
      auto p = p0;
      p0 = p1;
      p1 = successor(legendre)(c, x, p0, p);
      ++c;
    }
    return if_else(out_of_range, allbits, p1);
  }

  template<decorator Kind, integral_simd_value I, floating_scalar_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const & k
                                , I nn, T x) noexcept
  requires(is_one_of<Kind>(types<p_kind_type, q_kind_type> {}))
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return k(legendre)(nn, f_t(x));
  }

  template<decorator Kind, integral_simd_value I, floating_simd_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const & k
                                , I nn, T x) noexcept
  requires(is_one_of<Kind>(types<p_kind_type, q_kind_type> {}) && index_compatible_values<I, T>)
  {
    if (has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto p0 = one(as(x));
      T p00;
      auto iseqzn = is_eqz(nn);
      auto p1 = x;
      auto out_of_range = eve::abs(x) > one(as(x));

      if constexpr(std::same_as<Kind, p_kind_type>)
      {
        if(eve::all(iseqzn)) return if_else(out_of_range, allbits, p0);
      }
      else if constexpr(std::same_as<Kind, q_kind_type>)
      {
        p0 = atanh(x);
        p00 = p0;
        if(eve::all(iseqzn)) return if_else(out_of_range, allbits, p0);
        p1 = fms(x, p0, one(as(x)));
      }
      auto n = convert(nn, as<elt_t>());
      auto c = one(as(n));
      auto test = c < n;
      while(eve::any(test))
      {
        auto p = p0;
        p0 = p1;
        p1 = if_else(test, successor(legendre)(c, x, p0, p), p1);
        c = inc(c);
        test = c < n;
      }
      if constexpr(std::same_as<Kind, p_kind_type>)
        p1 = if_else(iseqzn, one, p1);
      else if constexpr(std::same_as<Kind, q_kind_type>)
        p1 = if_else(iseqzn, p00, p1);
      return if_else(out_of_range, allbits, p1);
    }
    else
      return apply_over(k(legendre), nn, x);
  }
  /////////////////////////////////////////////////////////////////////////////////
  // associated legendre p polynomials

  // Recurrence relation for associated p legendre polynomials
  template <real_value L, real_value M, floating_value T>
  EVE_FORCEINLINE T legendre_(EVE_SUPPORTS(cpu_), successor_type const &
                             , L l, M m, T x, T pl, T plm1) noexcept
  {
    auto lp1= inc(l);
    return fms((lp1 + l) * x, pl, (l+m) * plm1)/ (lp1-m);
  }

  template<integral_scalar_value L, integral_scalar_value M, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l, M m, T x) noexcept
  {
    if(eve::abs(x) > one(as(x)))return nan(as(x));
    // Handle negative arguments first:
    T sin_theta_power = eve::pow_abs(oneminus(sqr(x)), T(eve::abs(m))/2); //TODO
    if(l < 0)                   return legendre(-l-1, m, x);
    if ((l == L(0)) && (m == M(-1)))  return eve::sqrt(oneminus(x)/(inc(x)));
    if ((l == L(1)) && (m == M(0)))   return x;
    if (-m == l) return pow((1 - x * x) / 4, T(l) / 2) / eve::tgamma(T(inc(l))); //TODO factorial
    if(m < 0)  {
      auto tgr = [](auto a,  auto b){ return tgamma(a)/tgamma(b); };
      int sign = (m&M(1)) ? -1 : 1;
      return sign * tgr(T(l+m+1), T(l+1-m)) * legendre(l, -m, x);
    }

    // Special cases:
    if(m > l ) return T(0);
    if(m == 0) return legendre(l, x);
    T p0 = T(eve::double_factorial(unsigned(2 * m - 1))) * sin_theta_power;
    if(m&1) p0 *= -1;
    if(m == l) return p0;
    T p1 = x * (2 * m + 1) * p0;
    auto n = inc(m);
    while(n < l)
    {
      auto p = p0;
      p0 = p1;
      p1 = successor(legendre)(n, m, x, p0, p);
      ++n;
    }
    return p1;
  }

//   template<integral_simd_value M, integral_simd_value N, floating_scalar_value T>
//   EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), N nn,  M mm, T x) noexcept
//   {
//    if (has_native_abi_v<T>)
//     {
//       auto iseqzm = is_eqz(mm);
//       if(eve::all(iseqzm)) [[unlikely]]
//       {
//         return legendre(nn, x);
//       }
//       else [[likely]]
//       {
//         using elt_t = element_type_t<T>;
//         auto p0 = one(as(x));
//         auto iseqzn = is_eqz(nn);
//         if(eve::all(iseqzn)) [[unlikely]]
//         {
//           return p0;
//         }
//         else [[likely]]
//         {
//           auto m =  convert(mm, as<elt_t>());
//           auto p1 = inc(m) - x;

//           auto n =  convert(nn, as<elt_t>());
//           auto c = one(as(n));;
//           auto test = c < n;
//           while(eve::any(test))
//           {
//             auto p = p0;
//             p0 = p1;
//             p1 = if_else(test, successor(legendre)(c, m, x, p0, p), p1);
//             c = inc(c);
//             test = c < n;
//           }
//           return  if_else(iseqzn, one, if_else(iseqzm,  legendre(n, x), p1));
//         }
//       }
//     }
//     else
//       return apply_over(legendre, nn, mm, x);
//   }
  ////////////////////////////////////////////////////////////////////////////////
}
