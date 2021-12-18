//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/proba/detail/attributes.hpp>
#include <eve/module/proba/detail/urg01.hpp>
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
#include <eve/function/lgamma.hpp>
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
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>

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
      if constexpr(scalar_value<value_type>) init();
    }

    using rejdata = struct
    {
      value_type b;
      value_type a;
      value_type c;
      value_type vr;
      value_type alpha;
      value_type lpq;
      value_type m;
      value_type h;
    };

    EVE_FORCEINLINE void init() noexcept
    requires scalar_value<value_type>
    {
      auto spq = eve::sqrt(n*p*q);
      rej.b = fma(spq, value_type(2.53), value_type(1.15));
      auto invb = rec(rej.b);
      rej.a = fma(value_type(0.01), eve::min(p, q), fma(rej.b, value_type(0.0248), value_type(-0.0873)));
      rej.c = fma(n, eve::min(p, q), value_type(0.5));
      rej.vr = fma(invb,value_type(-4.2), value_type(0.92));
      rej.alpha = spq*fma(invb, value_type(5.1), value_type(2.83));
      rej.lpq = eve::log(eve::min(p, q)/eve::max(p, q));
      rej.m = (floor(inc(n)*eve::min(p, q)));
      rej.h = (lgamma(inc(rej.m))+lgamma(inc(n-rej.m)));
     }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {

      auto flip = half(as(p)) < p;
      auto pp = (flip)? q : p;
      auto qq = oneminus(pp);
      if (inc(n)*p < value_type(11))
      {
        auto s = pp / qq;
        auto a = inc(n)*s;
        R r(pow_abs(qq, n));//const ?
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
        auto gen1 = [this, &gen](auto v, R& us, R& k){
          auto u = detail::urg01(gen, as<R>())-R(0.5);
          us= R(0.5)- eve::abs(u);
          k = floor(fma(fma(R(2), rej.a/us, rej.b), u, rej.c));
          auto t = (us >= R(0.07)) && (v <= rej.vr);
          k = if_else(t, k, allbits);
        };
        auto gen2= [&](){
          R v, us, k1, k(nan(as<R>()));
          auto isknan = is_nan(k);
          while (any(isknan))
          {
            v = detail::urg01(gen, as<R>());
            gen1(v, us, k1);
            k = if_else(isknan, k1, k);
            isknan = is_nan(k);
          }

          v *= rej.alpha/(rej.a/sqr(us)+rej.b);
          auto kdone = (v <= (lgamma(inc(k))+lgamma(inc(n-k))-rej.h)+(k-rej.m)*rej.lpq);
          k =  if_else(kdone, k, allbits);
          return if_else(flip, n-k, k);
        };

        R k = nan(as<R>());
        auto isknan = is_nan(k);
        while (any(isknan))
        {
          auto k1 = gen2();
          k = if_else(isknan, k1, k);
          isknan = is_nan(k);
        }
        return k;
      }
    }


    n_type n;
    p_type p, q;
    rejdata rej;
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

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return if_else(detail::urg01(gen, as<R>()) < p, zero, one(as<R>()));
//      return binarize(detail::urg01(gen, as<R>()) < p);
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
      if constexpr(scalar_value<value_type>) init();
    }

    using rejdata = struct
    {
      value_type spq;
      value_type b;
      value_type a;
      value_type c;
      value_type vr;
      value_type alpha;
      value_type lpq;
      value_type m;
      value_type h;
    };

    EVE_FORCEINLINE void init() noexcept
    requires scalar_value<value_type>
    {
      const auto p =  value_type(0.5);
      auto spq = eve::sqrt(n)*p;
      rej.b = fma(spq, value_type(2.53), value_type(1.15));
      auto invb = rec(rej.b);
      rej.a = fma(value_type(0.01), p, fma(rej.b, value_type(0.0248), value_type(-0.0873)));
      rej.c = fma(n, p, p);
      rej.vr = fma(invb,value_type(-4.2), value_type(0.92));
      rej.alpha = spq*fma(invb, value_type(5.1), value_type(2.83));
      rej.m = floor(inc(n)*p);
      rej.h = lgamma(inc(rej.m))+lgamma(inc(n-rej.m));
     }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
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
        auto gen1 = [this, &gen](auto v, R& us, R& k){
          auto u = detail::urg01(gen, as<R>())-R(0.5);
          us= R(0.5)- eve::abs(u);
          k = floor(fma(fma(R(2), rej.a/us, rej.b), u, rej.c));
          auto t = (us >= R(0.07)) && (v <= rej.vr);
          k = if_else(t, k, allbits);
        };
        auto gen2= [&](){
          R v, us, k1, k(nan(as<R>()));
          auto isknan = is_nan(k);
          while (any(isknan))
          {
            v = detail::urg01(gen, as<R>());
            gen1(v, us, k1);
            k = if_else(isknan, k1, k);
            isknan = is_nan(k);
          }

          v *= rej.alpha/(rej.a/sqr(us)+rej.b);
          auto kdone = (v <= (lgamma(inc(k))+lgamma(inc(n-k)))-rej.h);
          k =  if_else(kdone, k, allbits);
          return k;
        };

        R k = nan(as<R>());
        auto isknan = is_nan(k);
        while (any(isknan))
        {
          auto k1 = gen2();
          k = if_else(isknan, k1, k);
          isknan = is_nan(k);
        }
        return k;
      }
    }

    value_type n;
    value_type exp2mn;
    rejdata rej;
  };

  template<typename T, typename U>  binomial_distribution(T,U) -> binomial_distribution<T,U>;

  template < floating_real_value T>
  struct binomial_distribution<callable_one_, callable_half_, T>
  {
    using is_distribution_t = void;
    using n_type = callable_one_;
    using p_type = callable_half_;
    using value_type = T;

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return binarize(detail::urg01(gen, as<R>()) > R(0.5));
    }

    constexpr binomial_distribution( as<T> const&) {}
  };

  template<typename T>  binomial_distribution(as<T> const&) -> binomial_distribution<callable_one_, callable_half_, T>;

  template<floating_real_value T>
  inline constexpr auto bernouilli = binomial_distribution<callable_one_, callable_half_, T>(as<T>{});

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
        return half(as<T>())*eve::log(twopie*d.n*d.p*d.q); // + o(1/n)
      else if constexpr (floating_value<U>)
        return half(as<U>())*eve::log(twopie*d.n*U(0.25)); // + o(1/n)
      else if constexpr (floating_value<T>)
        return half(as<T>())*eve::log(twopie*d.p*d.q); // + o(1/n)
      else
        return half(as<I>())*eve::log(twopie*I(0.25)); // + o(1/n)
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
