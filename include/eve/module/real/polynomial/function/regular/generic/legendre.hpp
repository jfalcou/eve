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
#include <eve/function/is_odd.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/pow1p.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/p_kind.hpp>
#include <eve/function/q_kind.hpp>
#include <eve/function/successor.hpp>
#include <utility>

namespace eve::detail
{
  // basic legendre (legendre_p)
  template<real_value L, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l, T x) noexcept
  {
    EVE_ASSERT(l >= 0 && is_flint(l), "legendre(l, x): l is negative or not integral");
    return p_kind(legendre)(l, x);
  }

  // Recurrence relation for legendre polynomials of all kinds
  template <real_value L, floating_value T>
  EVE_FORCEINLINE T legendre_(EVE_SUPPORTS(cpu_), successor_type const &
                             , L l, T x, T pl, T plm1) noexcept
  {
    EVE_ASSERT(l >= 0 && is_flint(l), "successor(legendre)(l, x, pl, plm1): l is negative or not integral");
    auto lp1= inc(l);
    return fms((lp1 + l) * x, pl, l * plm1)/ lp1;
  }

  // decorated p_kind, q_kind,  scalar index:
  template<decorator Kind, real_scalar_value L, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const &
                                , L l, T x) noexcept
  {
    if constexpr(std::same_as<Kind, p_kind_type>) EVE_ASSERT(is_flint(l)&&(l >= 0), "p_kind(legendre)(l, x): l is negative or not integral");
    if constexpr(std::same_as<Kind, q_kind_type>) EVE_ASSERT(is_flint(l)&&(l >= 0), "q_kind(legendre)(l, x): l is negative or not integral");
    auto out_of_range = eve::abs(x) > one(as(x));
    if (l < 0) l = -l-1;  //reflection formula
    auto p0 = one(as(x));
    auto p1 = x;
    if constexpr(std::same_as<Kind, p_kind_type>)
    {
      if(is_eqz(l)) return if_else(out_of_range, allbits, p0);
    }
    else if constexpr(std::same_as<Kind, q_kind_type>)
    {
      p0 = eve::atanh(x);
      if(is_eqz(l)) return if_else(out_of_range, allbits, p0);
      p1 = fms(x, p0, one(as(x)));
    }
    auto c = one(as(l));
    while(c < l)
    {
      auto p = p0;
      p0 = p1;
      p1 = successor(legendre)(c, x, p0, p);
      ++c;
    }
    return if_else(out_of_range, allbits, p1);
  }

  template<decorator Kind, integral_simd_value L, floating_scalar_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const & k
                                , L l, T x) noexcept
  requires(is_one_of<Kind>(types<p_kind_type, q_kind_type> {}))
  {
    using f_t = as_wide_t<T, cardinal_t<L>>;
    return k(legendre)(l, f_t(x));
  }

  template<decorator Kind, real_simd_value L, floating_simd_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const & k
                                , L l, T x) noexcept
  requires(is_one_of<Kind>(types<p_kind_type, q_kind_type> {}) && (cardinal_v<L> == cardinal_v<T>))
  {
    EVE_ASSERT(l >= 0 && is_flint(l), "legendre(l, x): l is negative or not integral");
    if (has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto p0 = one(as(x));
      T p00;
      auto iseqzn = is_eqz(l);
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
      auto n = convert(l, as<elt_t>());
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
      return apply_over(k(legendre), l, x);
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

  template<real_scalar_value L, real_scalar_value M, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l, M m, T x) noexcept
  {
    if(eve::abs(x) > one(as(x))) return nan(as(x));
    // Handle negative arguments first:
    T sin_theta_power = eve::pow1p(-sqr(x), T(eve::abs(m))/2);
    if(l < 0)                   return legendre(-l-1, m, x);
    if ((l == L(0)) && (m == M(-1)))  return eve::sqrt(oneminus(x)/(inc(x)));
    if ((l == L(1)) && (m == M(0)))   return x;
    if (-m == l)
    {
      return pow((1 - x * x) / 4, T(l) / 2) / eve::tgamma(T(inc(l))); //TODO factorial and 1-x*x
    }
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

  template<integral_simd_value M, integral_simd_value L, floating_value T>
  EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l,  M m, T x) noexcept
  {
   if (has_native_abi_v<T>)
    {
      auto iseqzm = is_eqz(m);
      if(eve::all(iseqzm)) [[unlikely]]
      {
        return legendre(l, x);
      }
      else [[likely]]
      {
        auto lneg = is_ltz(l);
        auto mneg = is_ltz(m);

        auto notdone = (eve::abs(x) <= one(as(x)));
        auto r = if_else(m > l, zero, nan(as(x)));
        if (eve::any(notdone))
        {
          auto lneg_case = [](auto l, auto m, auto x) {
            return legendre(-l-1, m, x);
          };
          auto t1_case = [](auto x) {  //is_eqz(l) && (m == mone(as(m)));
            return eve::sqrt(oneminus(x)/(inc(x)));
          };

          auto t2_case = [](auto l, auto x) {  // (-m == l)
            return pow((1 - x * x) / 4, T(l) / 2) / eve::tgamma(T(inc(l))); //TODO factorial and 1-x*x
          };

          auto mneg_case = [mneg](auto ll, auto mm, auto x) {  // (m < 0)
            using elt_t =  element_type_t<T>;
            auto l = convert(ll, as<elt_t>());
            auto m = convert(mm, as<elt_t>());
            auto sign = if_else(is_odd(m), mone, one(as(m)));
            return sign * tgamma(l+m+1)/tgamma(l+1-m) * legendre(ll, minus[mneg](mm), x);
          };

          auto t3_case = [](auto x) {  //(l == one(as(l)) && iseqz(m));
            return x;
          };

          auto t4_case = [](auto x) {  //(m > l);
            return zero(as(x));
          };

          auto t5_case = [](auto l, auto x) {  //(m == 0);
            return legendre(l, x);
          };

          auto t6_case = [](auto ll, auto mm, auto x) {
            using elt_t =  element_type_t<T>;
            auto l = convert(ll, as<elt_t>());
            auto m = convert(mm, as<elt_t>());
            using r_t =  decltype(x*l*m);
            auto sin_theta_power = eve::pow1p(-sqr(x), eve::abs(m)/2);
            r_t p0 = convert(eve::double_factorial(uint_(2*mm-1)), as<elt_t>()) * sin_theta_power;
            p0 = if_else(is_odd(m), -p0, p0);
            auto p00 = p0;
            auto p1 = x * (2 * m + 1) * p0;
            auto n = inc(m);
            auto test = n < l;
            while(eve::any(test))
            {
              auto p = p0;
              p0 = p1;
              p1 = successor(legendre)(n, m, x, p0, p);
              n = inc(n);
              test = n < l;
            }
            p0 = if_else(is_odd(p0), -p0, p0);
            return if_else(m == l, p00, p0);
          };

          notdone = next_interval(lneg_case,  notdone, lneg, r, l, m, x);
          if( eve::any(notdone) )
          {
            auto t1 = is_eqz(l) && (m == mone(as(m)));
            notdone = next_interval(t1_case,  notdone, t1, r, x);
            if( eve::any(notdone) )
            {
              auto t2 = -m == l; //m is < 0
              notdone = next_interval(t2_case,  notdone, t2, r, l, x);
              if( eve::any(notdone) )
              {
                notdone = next_interval(mneg_case,  notdone, mneg, r, l, m, x);
                if( eve::any(notdone) )
                {
                  auto t3 = l == one(as(l)) && iseqzm;
                  notdone = next_interval(t3_case,  notdone, t3, r, x);
                  if( eve::any(notdone) )
                  {
                    auto t4 = (m > l);
                    notdone = next_interval(t4_case,  notdone, t4, r, x);
                    if( eve::any(notdone) )
                    {
                      auto t5 = (m == 0);
                      notdone = next_interval(t5_case,  notdone, t5, r, l, x);
                      if( eve::any(notdone) )
                      {
                        notdone = last_interval(t6_case,  notdone, r, l, m, x);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        return r;
      }
    }
    else
      return apply_over(legendre, l, m, x);
  }

//   template<real_value M, real_value L, floating_value T>
//   EVE_FORCEINLINE auto aux_legendre(L l,  M m, T xs) noexcept
//   {
//     return legendre(l, m, xs);
//   }

}
