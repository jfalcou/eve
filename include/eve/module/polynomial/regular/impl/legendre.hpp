//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{
  // Recurrence relation for legendre polynomials of all kinds
  template<typename L, typename T, callable_options O>
  constexpr EVE_FORCEINLINE as_wide_as_t<T, L>
  legendre_(EVE_REQUIRES(cpu_), O const&, L l, T x, T pl, T plm1)
    requires(O::contains(successor))
  {
    EVE_ASSERT(eve::all(l >= 0 && is_flint(l)),
               "successor(legendre)(l, x, pl, plm1): l is negative or not integral");
    auto lp1 = inc(l);
    return fms((lp1 + l) * x, pl, l * plm1) / lp1;
  }

  // basic legendre (legendre_p)
  template<ordered_value L, floating_value T, callable_options O>
  as_wide_as_t<T, L>
  constexpr legendre_(EVE_REQUIRES(cpu_), O const& o, L l, T x)
  {
    EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "legendre(l, x): l is negative or not integral");
    using r_t = as_wide_as_t<T, L>;
    if constexpr(scalar_value<L>)
    {
      if constexpr(O::contains(p_kind) || O::contains(q_kind))
      {
        auto out_of_range = eve::abs(x) > one(as(x));
        if( l < 0 ) l = -l - 1; // reflection formula
        auto p0 = one(as(x));
        auto p1 = x;
        if constexpr(O::contains(p_kind))
        {
          if( is_eqz(l) ) return if_else(out_of_range, allbits, p0);
        }
        else if constexpr(O::contains(q_kind))
        {
          p0 = eve::atanh(x);
          if( is_eqz(l) ) return if_else(out_of_range, allbits, p0);
          p1 = fms(x, p0, one(as(x)));
        }
        auto c = one(as(l));
        while( c < l )
        {
          auto p = p0;
          p0     = p1;
          p1     = legendre[successor](c, x, p0, p);
          ++c;
        }
        return if_else(out_of_range, allbits, p1);
      }
      else return legendre[p_kind](l, x);
    }
    else if constexpr(simd_value<L>)
    {
      if (scalar_value<T>)
      {
        using r_t = as_wide_as_t<T, L>;
        return legendre_(EVE_TARGETS(cpu_), o, l, r_t(x));
      }
      else
      {
        if constexpr( has_native_abi_v<T> )
        {
          if constexpr(O::contains(p_kind) || O::contains(q_kind))
          {
            auto xx = r_t(x);
            using elt_t = element_type_t<T>;
            auto p0     = one(as(xx));
            r_t    p00;
            auto iseqzn       = is_eqz(l);
            auto p1           = xx;
            auto out_of_range = eve::abs(xx) > one(as(xx));

            if constexpr(O::contains(p_kind))
            {
              if( eve::all(iseqzn) ) return if_else(out_of_range, allbits, p0);
            }
            else if constexpr(O::contains(q_kind))
            {
              p0  = atanh(xx);
              p00 = p0;
              if( eve::all(iseqzn) ) return if_else(out_of_range, allbits, r_t(p0));
              p1 = fms(x, p0, one(as(xx)));
            }
            auto n    = convert(l, as<elt_t>());
            auto c    = one(as(n));
            auto test = c < n;
            while( eve::any(test) )
            {
              auto p = p0;
              p0     = p1;
              p1     = if_else(test, legendre[successor](c, xx, p0, p), p1);
              c      = inc(c);
              test   = c < n;
            }
            if constexpr(O::contains(p_kind))
              p1 = if_else(iseqzn, one, p1);
            else if constexpr(O::contains(q_kind) )
              p1 = if_else(iseqzn, p00, p1);
            return if_else(out_of_range, allbits, p1);
          }
          else return apply_over(legendre[p_kind], l, r_t(x));
        }
        else
        {
          if constexpr(O::contains(p_kind))
            return apply_over(legendre[p_kind], l, r_t(x));
          else
            return apply_over(legendre[q_kind], l, r_t(x));
        }
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////////////
  // associated legendre p polynomials

  // Recurrence relation for associated p legendre polynomials
  template<typename L, typename M, typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  legendre_(EVE_REQUIRES(cpu_), O const&, L l, M m, T x, T pl, T plm1)
    requires(O::contains(successor)&& O::contains(associated))
  {
    auto lp1 = inc(l);
    return fms((lp1 + l) * x, pl, (l + m) * plm1) / (lp1 - m);
  }

  template<typename L, typename M, typename T, callable_options O>
  constexpr as_wide_as_t<T, common_value_t<M, L>>
  legendre_(EVE_REQUIRES(cpu_), O const&, L l, M m, T x)
    requires(O::contains(associated)||O::contains(condon_shortley2)||O::contains(spherical2))
  {
    EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "legendre(l, m, x): l is negative or not integral");
    EVE_ASSERT(eve::all(m >= 0 && is_flint(l)), "legendre(l, m, x): m is negative or not integral");
    if constexpr(O::contains(spherical2))
    {
      auto ll   = convert(l, as_element(x));
      auto mm   = convert(m, as_element(x));
      using r_t = eve::common_value_t<T, decltype(ll), decltype(mm)>;
      r_t p0(x);
      p0 = eve::legendre[associated](l, m, eve::cos(p0));
      p0 *= sqrt(((2 * ll + 1) / (4 * pi(as(x))))
                 * exp(log_abs_gamma(ll - mm + 1) - log_abs_gamma(ll + mm + 1)));
      return if_else(is_odd(m), -p0, p0);
    }
    else if constexpr(O::contains(condon_shortley2))
    {
      auto p0 = legendre[associated](l, m, x);
      return if_else(is_odd(m), -p0, p0);
    }
    else if constexpr(scalar_value<M> && scalar_value<L>)
    {
      auto outofrange = eve::abs(x) > one(as(x));
      if( outofrange || (l < 0) || (m < 0) ) return nan(as(x));
      if( (l == L(1)) && (m == M(0)) ) return x;
      if( m > l ) return T(0);
      if( m == 0 ) return legendre(l, x);
      T sin_theta_power = eve::pow(1 - sqr(x), T(eve::abs(m)) / 2);
      T p0              = T(eve::double_factorial(unsigned(2 * m - 1))) * sin_theta_power;
      if( m == l ) return p0;
      T    p1 = x * (2 * m + 1) * p0;
      auto n  = inc(m);
      while( n < l )
      {
        auto p = p0;
        p0     = p1;
        p1     = legendre[associated][successor](n, m, x, p0, p);
        ++n;
      }
      return p1;
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto iseqzm = is_eqz(m);
        if( eve::all(iseqzm) )
        {
          return legendre(l, x);
        }
        else
        {
          auto lpos    = is_gez(l);
          auto mpos    = is_gez(m);
          auto mlel    = m <= l;
          auto inrange = eve::abs(x) <= one(as(x));
          auto notdone = inrange && lpos && mpos;
          auto r       = if_else(notdone, zero, nan(as(x)));
          notdone      = notdone && mlel;

          if( eve::any(notdone) )
          {
            auto mz_case = [](auto l, auto x) { //(m == 0);
              return legendre(l, x);
            };

            auto regular_case = [](auto ll, auto mm, auto x, auto notdone) { // other cases
              using elt_t          = element_type_t<T>;
              auto l               = convert(ll, as<elt_t>());
              auto m               = convert(mm, as<elt_t>());
              using r_t            = decltype(x * l * m);
              auto sin_theta_power = eve::pow1p(-sqr(x), eve::abs(m) / 2);

              r_t p0 = convert(eve::double_factorial(uint_(eve::max(2 * mm - 1, zero(as(mm))))),
                               as<elt_t>())
              * sin_theta_power;
              auto p00  = p0;
              auto p1   = x * (2 * m + 1) * p0;
              auto n    = if_else(notdone, inc(m), inc(l));
              auto test = (n < l);
              while( eve::any(test) )
              {
                auto p = p0;
                p0     = p1;
                p1     = if_else(test, legendre[associated][successor](n, m, x, p0, p), p1);
                n      = inc(n);
                test   = n < l;
              }
              return if_else(m == l, p00, p1);
            };
            auto mz = (m == 0);
            notdone = next_interval(mz_case, notdone, mz, r, l, x);
            if( eve::any(notdone) )
            {
              notdone = last_interval(regular_case, notdone, r, l, m, x, notdone);
            }
          }
          return r;
        }
      }
      else return apply_over(legendre[associated], l, m, x);
    }
  }
}
