//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/real/proba/detail/attributes.hpp>
#include <eve/module/real/proba/detail/urg01.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/all.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/beta.hpp>
#include <eve/function/betainc.hpp>
#include <eve/function/log.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <iostream>
#include <tts/tts.hpp>

namespace eve
{
  template < typename T, typename U, typename Internal = T>
  struct binomial_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct binomial_distribution<T, U>
  {
    using is_distribution_t = void;
    using n_type = T;
    using p_type = U;
    using value_type = common_compatible_t<T, U>;
    using elt_t = element_type_t<value_type>;

    binomial_distribution(T n_,  U p_)
      : n(n_), p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
      EVE_ASSERT(all(p < one(as(p)) && is_gez(p)), "p must be in ]0, 1[");
    }

//     template < integral_scalar_value N,  floating_real_value UU>
//     requires  std::convertible_to<T, N> && std::constructible_from<U, UU>
//     binomial_distribution(N n_,  UU p_)
//       : n(T(n_)), p(U(p_)), q(oneminus(p))
//     {
//       EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
//       EVE_ASSERT(all(p < one(as(p)) && is_gez(p)), "p must be in [0, 1]");
//     }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      auto pp = (half(as(p)) < p)? q : p;
      if (inc(n)*p < value_type(11))
      {
        auto qq = oneminus(pp);
        auto s = pp / qq;
        auto a = inc(n)*s;
        R r(pow_abs(qq, n));//const ?
//         std::cout << tts::typename_of_(p) << std::endl;
//         std::cout << std::endl << "p " << p << std::endl;
//         std::cout << std::endl << "q " <<q << std::endl;
//         std::cout << std::endl << "pp " << pp << std::endl;
//          std::cout << std::endl << "qq " << qq << std::endl;
//         std::cout << "r " << r << std::endl;
        auto u = detail::urg01(gen, as<R>());
        auto x(zero(as<R>()));
        auto r1(inf(as<R>()));
        auto t = u > r;
        while(any(t))
        {
          u = sub[t](u, r);
          x = inc[t](x);
          r1 = if_else(t, (a/x-s)*r, r1);
          if constexpr(std::same_as<elt_t, float>)
            // If r gets too small then the round-off error
            // becomes a problem.  At this point, p(i) is
            // decreasing exponentially, so if we just call
            // it 0, it's close enough.  Note that the
            // minimum value of q_n is about 1e-7, so we
            // may need to be a little careful to make sure that
            // we don't terminate the first time through the loop
            // for float.  (Hence the test that r is decreasing)
            if(all(r1 < eps(as<R>()) && r1 < r)) break;
          r = r1;
          t = u > r;
        }
        return x;
       }
      else
      {
        return R();
      }
    }

    n_type n;
    p_type p, q;
  };

  template < floating_real_value U>
  struct binomial_distribution<callable_one_, U>
  {
    using is_distribution_t = void;
    using n_type = callable_one_;
    using p_type = U;
    using value_type = U;
    using elt_t = element_type_t<value_type>;


    binomial_distribution(callable_one_ const&, U p_)
      : p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    p_type p, q;
  };

  template < floating_real_value T>
  struct binomial_distribution<T, callable_half_>
  {
    using is_distribution_t = void;
    using n_type = T;
    using p_type = callable_half_;
    using value_type = T;
    using elt_t = element_type_t<value_type>;

    binomial_distribution(T n_, callable_half_ const &)
      : n(n_), exp2mn(exp2(-n))
    {
      EVE_ASSERT(all(is_finite(n) && is_gtz(n)), "n must be finite and strictly positive");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      if (n < value_type(21))
      {
        R r(exp2mn);
        auto a = inc(n);
        auto u = detail::urg01(gen, as<R>());
        auto x(zero(as<R>()));
        auto r1(inf(as<R>()));
        auto t = u > r;
        while(any(t))
        {
          u = sub[t](u, r);
          x = inc[t](x);
          r1 = if_else(t, dec(a/x) * r, r1);
           if constexpr(std::same_as<elt_t, float>)
             // If r gets too small then the round-off error
             // becomes a problem.  At this point, p(i) is
             // decreasing exponentially, so if we just call
             // it 0, it's close enough.  Note that the
             // minimum value of q_n is about 1e-7, so we
             // may need to be a little careful to make sure that
             // we don't terminate the first time through the loop
             // for float.  (Hence the test that r is decreasing)
             if(all(r1 < eps(as<R>()) && r1 < r)) break;
          r = r1;
          t = u > r;
        }
        return x;
       }
      else
      {
        auto sqrtn =  eve::sqrt(n);
        auto c = half(as<R>())*inc(n);
        auto b = fma(eve::sqrtn, 1.265, 1.15);
        auto a = fma(0.01, pp, fma(b, 0.0248, -0.0873));
        auto alpha = 0.5*(2.83+5.1/b)*sqrtn;
        auto ur = 0.43;
        auto vr = 0.92-4.2/b;
        auto urvr = ur*vr;
        auto k(mone(as<R>()));
        auto knotdone = is_ltz(k) || (k >  n);
        while (any(knotdone))
        {

          auto v = detail::urg01(gen, as<R>());

          auto done = v <= ur*vr;
          auto vu = v/vr-0.43;
          auto z1_done = eve::floor(fma(2*a/(half(as<R>())-eve::abs(vu))+b, vu, c));

          auto t1 v >= vr;
          auto u_t1 = detail::urg01(gen, as<R>())-half(as<R>());
          auto u_nott1 = v/vr-0.93;
          auto u_nott1 = sign(u)*0.5-u_nott1
            auto v_nott1 = detail::urg01(gen, as<R>())*vr;

          auto u = if_else(t1, u_t1, u_nott1);

          auto us = half(as<R>())-eve::abs(u);
          auto k  = floor(fma(fma(2, a/us, bà), u, c));
          knotdone = is_ltz(k) || (k >  n);

        auto z2_nott1 =
        return R();
      }
    }

    value_type n;
    value_type exp2mn;
  };

  template<typename T, typename U>  binomial_distribution(T,U) -> binomial_distribution<T,U>;

  template < floating_real_value T>
  struct binomial_distribution<callable_one_, callable_half_, T>
  {
    using is_distribution_t = void;
    using n_type = callable_one_;
    using p_type = callable_half_;
    using value_type = T;

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      return binarize(detail::urg01(gen, as<R>()) > R(0.5));
    }

    constexpr binomial_distribution( as_<T> const&) {}
  };

  template<typename T>  binomial_distribution(as_<T> const&) -> binomial_distribution<callable_one_, callable_half_, T>;

  template<floating_real_value T>
  inline constexpr auto bernouilli = binomial_distribution<callable_one_, callable_half_, T>(as_<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , binomial_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      auto k = floor(x);
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(is_ltz(x), zero, if_else(x < one(as(x)),  betainc(d.q, d.n-k, inc(k)), one));
      else if constexpr(std::same_as<T, callable_one_> && floating_value<U>)
        return if_else(is_ltz(x), zero, if_else(x < one(as(x)), d.q, one));
      else if constexpr(std::same_as<U, callable_half_> && floating_value<T>)
        return  betainc(half(as(x)), d.n-k, inc(k));
      else
        return if_else(is_ltz(x), zero, if_else(x < one(as(x)), half(as(x)), one));
    }

    //////////////////////////////////////////////////////
    /// pmf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , binomial_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        auto fk = eve::min(eve::max(floor(x), zero(as(x))), d.n);
        auto nmk = d.n-fk;
        return pow_abs(d.p, fk)*pow_abs(d.q, nmk)*beta(inc(fk), inc(nmk))/inc(d.n);
      }
      else if constexpr(std::same_as<T, callable_one_> && floating_value<U>)
      {
        auto fk = eve::min(eve::max(floor(x), zero(as(x))), one(as(x)));
        return if_else(is_eqz(fk), d.q, if_else(fk == one(as(fk)), d.p, zero));
      }
      else if constexpr(std::same_as<U, callable_half_> && floating_value<T>)
      {
        auto fk = eve::min(eve::max(floor(x), zero(as(x))), d.n);
        auto nmk = d.n-fk;
        return d.exp2mn*beta(inc(fk), inc(nmk)*half(as(x)));
      }
      else
        return if_else(is_eqz(x) || (x == one(as(x))), half(as(x)), zero);
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , binomial_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return pow_abs(fma(d.p, exp(x), d.q), d.n);
      }
      else if constexpr(std::same_as<T, callable_one_> && floating_value<U>)
      {
        return fma(d.p, exp(x), d.q);
      }
      else if constexpr(std::same_as<U, callable_half_> && floating_value<T>)
      {
        return eve::sqrt(fma(d.p, exp(x), d.q));
      }
      else
        return half(as(x))*inc(exp(x));
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , binomial_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  floor(d.p*d.n);
      else if constexpr (floating_value<U>)
        return  floor(d.p);
      else if constexpr (floating_value<T>)
        return  floor(half(as<T>())*d.n);
      else
        return zero(as<I>());
    }


    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , binomial_distribution<T,U,I> const &d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  d.p*d.n;
      else if constexpr (floating_value<U>)
        return  d.p;
      else if constexpr (floating_value<T>)
        return  half(as<T>())*d.n ;
      else
        return half(as<I>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , binomial_distribution<T,U,I> const & d) noexcept
    {
      return median(d);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , binomial_distribution<T,U,I> const & d) noexcept
    {
      auto twopie = T(17.0794684453471341309271017390931489900697770715304);
      if constexpr (floating_value<U> && floating_value<T>)
        return half(as<T>())*eve::log(twopie*d.n*d.p*d.q); // + ô(1/n)
      else if constexpr (floating_value<U>)
        return half(as<U>())*eve::log(twopie*d.n*U(0.25)); // + ô(1/n)
      else if constexpr (floating_value<T>)
        return half(as<T>())*eve::log(twopie*d.p*d.q); // + ô(1/n)
      else
        return half(as<I>())*eve::log(twopie*I(0.25)); // + ô(1/n)
    }


    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , binomial_distribution<T,U,I> const & d ) noexcept
    {
      if constexpr (floating_value<T>)
        return (d.q-d.p)/stdev(d);
      else if constexpr (floating_value<U>)
        return zero(as<U>());
      else
        return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , binomial_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>)
        return oneminus(6*d.p*d.q)/var(d);
      else if constexpr (floating_value<U>)
        return half(as<T>())/var(d);
      else
        return I(-2);
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , binomial_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>&&(floating_value<U>))
        return d.n*d.p*d.q;
      else if constexpr (floating_value<T>)
        return T(0.25)*d.n;
      else if constexpr (floating_value<U>)
        return d.p*d.q;
      else
        return I(0.25);
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                , binomial_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>&&(floating_value<U>))
        return eve::sqrt(d.n*d.p*d.q);
      else if constexpr (floating_value<T>)
        return T(0.5)*eve::sqrt(d.n);
      else if constexpr (floating_value<U>)
        return eve::sqrt(d.p*d.q);
      else
        return I(0.5);
    }
  }
}
