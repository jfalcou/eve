//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/detail/hz_device.hpp>

namespace eve
{
  //================================================================================================
  //================================================================================================
  // Function decorators mark-up used in asociated legendre overload overload
  struct condon_shortey_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };
  using condon_shortey_type = decorated<condon_shortey_()>;
  inline constexpr condon_shortey_type const condon_shortey = {};

  namespace detail
  {
    // basic legendre (legendre_p)
    template<real_value L, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l, T x) noexcept
    {
      EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "legendre(l, x): l is negative or not integral");
      return p_kind(legendre)(l, x);
    }

    // Recurrence relation for legendre polynomials of all kinds
    template <real_value L, floating_value T>
    EVE_FORCEINLINE T legendre_(EVE_SUPPORTS(cpu_), successor_type const &
                               , L l, T x, T pl, T plm1) noexcept
    {
      EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "successor(legendre)(l, x, pl, plm1): l is negative or not integral");
      auto lp1= inc(l);
      return fms((lp1 + l) * x, pl, l * plm1)/ lp1;
    }

    // decorated p_kind, q_kind,  scalar index:
    template<decorator Kind, real_scalar_value L, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), Kind const &
                                  , L l, T x) noexcept
    {
      if constexpr(std::same_as<Kind, p_kind_type>) EVE_ASSERT(is_flint(l)&&eve::all((l >= 0)), "p_kind(legendre)(l, x): l is negative or not integral");
      if constexpr(std::same_as<Kind, q_kind_type>) EVE_ASSERT(is_flint(l)&&eve::all((l >= 0)), "q_kind(legendre)(l, x): l is negative or not integral");
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

    template<decorator Kind, real_simd_value L, floating_scalar_value T>
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
      EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "legendre(l, x): l is negative or not integral");
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
      //   return     ((lp1 + l) * x* pl- (l+m) * plm1)/ (lp1-m);
    }

    template<real_value M, real_value L, floating_value T>
    EVE_FORCEINLINE auto aux_legendre(L l,  M m, T xs) noexcept
    {
      return legendre(l, m, xs);
    }

    template<real_scalar_value L, real_scalar_value M, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l, M m, T x) noexcept
    {
      EVE_ASSERT(l >= 0 && is_flint(l), "legendre(l, m, x): l is negative or not integral");
      EVE_ASSERT(m >= 0 && is_flint(l), "legendre(l, m, x): m is negative or not integral");
      auto outofrange = eve::abs(x) > one(as(x));
      if (outofrange || (l < 0) || (m < 0)) return nan(as(x));
      if ((l == L(1)) && (m == M(0))) return x;
      if (m > l ) return T(0);
      if (m == 0) return legendre(l, x);
      T sin_theta_power = eve::pow(1-sqr(x), T(eve::abs(m))/2);
      T p0 = T(eve::double_factorial(unsigned(2 * m - 1))) * sin_theta_power;
      if (m == l) return p0;
      T p1 = x * (2 * m + 1) * p0;
      auto n = inc(m);
      while (n < l)
      {
        auto p = p0;
        p0 = p1;
        p1 = successor(legendre)(n, m, x, p0, p);
        ++n;
      }
      return p1;
    }

    template<real_simd_value M, real_simd_value L, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), L l,  M m, T x) noexcept
    {
      EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "legendre(l, m, x): l is negative or not integral");
      EVE_ASSERT(eve::all(m >= 0 && is_flint(l)), "legendre(l, m, x): m is negative or not integral");
      if (has_native_abi_v<T>)
      {
        auto iseqzm = is_eqz(m);
        if(eve::all(iseqzm)) [[unlikely]]
        {
          return legendre(l, x);
        }
        else [[likely]]
        {
          auto lpos = is_gez(l);
          auto mpos = is_gez(m);
          auto mlel = m <= l;
          auto inrange = eve::abs(x) <= one(as(x));
          auto notdone = inrange && lpos && mpos;
          auto r = if_else(notdone, zero, nan(as(x)));
          notdone = notdone && mlel;

          if (eve::any(notdone))
          {
            auto mz_case = [](auto l, auto x) {  //(m == 0);
              return legendre(l, x);
            };

            auto regular_case = [](auto ll, auto mm, auto x, auto notdone) { // other cases
              using elt_t =  element_type_t<T>;
              auto l = convert(ll, as<elt_t>());
              auto m = convert(mm, as<elt_t>());
              using r_t =  decltype(x*l*m);
              auto sin_theta_power = eve::pow1p(-sqr(x), eve::abs(m)/2);

              r_t p0 = convert(eve::double_factorial(uint_(eve::max(2*mm-1, zero(as(mm))))), as<elt_t>()) * sin_theta_power;
              auto p00 = p0;
              auto p1 = x * (2 * m + 1) * p0;
              auto n = if_else(notdone, inc(m), inc(l));
              auto test = (n < l);
              while(eve::any(test))
              {
                auto p = p0;
                p0 = p1;
                p1 = if_else(test, successor(legendre)(n, m, x, p0, p), p1);
                n = inc(n);
                test = n < l;
              }
              return if_else(m == l, p00, p1);
            };
            auto mz = (m == 0);
            notdone = next_interval(mz_case,  notdone, mz, r, l, x);
            if( eve::any(notdone) )
            {
              notdone = last_interval(regular_case,  notdone, r, l, m, x, notdone);
            }
          }
          return r;
        }
      }
      else
        return apply_over(legendre, l, m, x);
    }


    template<real_value M, real_value L, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), condon_shortey_type const &
                                  , L l,  M m, T x) noexcept
    {
      auto p0 = legendre(l, m, x);
      return if_else(is_odd(m), -p0, p0);
    }

    template<real_value M, real_value L, floating_value T>
    EVE_FORCEINLINE auto legendre_(EVE_SUPPORTS(cpu_), sph_type const &
                                  , L l,  M m, T theta) noexcept
    {
      EVE_ASSERT(eve::all(l >= 0 && is_flint(l)), "sph(legendre)(l, m, theta): l is negative or not integral");
      EVE_ASSERT(eve::all(m >= 0 && is_flint(m)), "sph(legendre)(l, m, theta): m is negative or not integral");
      EVE_ASSERT(eve::all(m <= l)               , "sph(legendre)(l, m, theta): some m are greater than l");
      auto ll = convert(l, as<element_type_t<T>>());
      auto mm = convert(m, as<element_type_t<T>>());
      using r_t =  eve::common_compatible_t < T, decltype(ll), decltype(mm)>;
      r_t p0(theta);
      p0 = eve::legendre(l, m, cos(p0));
      p0 *= sqrt(((2*ll+1)/(4*pi(as(theta))))*exp(lgamma(ll-mm+1)-lgamma(ll+mm+1)));
     return if_else(is_odd(m), -p0, p0);
    }


  }
}
