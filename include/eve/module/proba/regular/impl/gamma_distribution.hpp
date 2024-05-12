//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/proba/detail/attributes.hpp>
#include <eve/module/proba/detail/urg01.hpp>
#include <eve/module/proba/regular/exponential_distribution.hpp>

namespace eve
{
 template < typename T, typename U, typename Internal = T>
  struct gamma_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct gamma_distribution<T, U>
  {
    using is_distribution_t = void;
    using k_type = T;
    using theta_type = U;
    using value_type = common_compatible_t<T, U>;
    using parameters = struct { value_type m; value_type s; };

    gamma_distribution(T k_,  U theta_)
      : k(k_), theta(theta_), invgk(tgamma(k_))
    {
      EVE_ASSERT(all(is_gtz(theta) && is_finite(theta)), "theta must be strictly positive and finite");
      EVE_ASSERT(all(is_gtz(k) && is_finite(k)), "k must be strictly positive and finite");
    }

    gamma_distribution(parameters const & p)
      : k(p.k), theta(p.theta)
    {
      EVE_ASSERT(all(is_gtz(theta) && is_finite(theta)), "theta must be strictly positive and finite");
      EVE_ASSERT(all(is_gtz(k) && is_finite(k)), "k must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .k = k, .theta = theta };
    }

    k_type k;
    theta_type theta;
    value_type invgk;
  };

  template < floating_real_value U>
  struct gamma_distribution<callable_one_, U>
  {
    using is_distribution_t = void;
    using k_type = callable_one_;
    using theta_type = U;
    using value_type = U;
    using parameters = struct { callable_one_ m;  value_type s;};

    gamma_distribution(callable_one_ const&, U theta_)
      : theta(theta_)
    {
      EVE_ASSERT(all(is_gtz(theta) && is_finite(theta)), "theta must be strictly positive and finite");
    }

    gamma_distribution(parameters const & p)
      : theta(p.theta)
    {
      EVE_ASSERT(all(is_gtz(theta) && is_finite(theta)), "theta must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
     return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() noexcept
    {
      return { .k = one, .theta = theta };
    }

    theta_type theta;
  };

  template < floating_real_value T>
  struct gamma_distribution<T, callable_one_>
  {
    using is_distribution_t = void;
    using k_type = T;
    using theta_type = decltype(eve::one);
    using value_type = T;
    using parameters = struct { value_type m;  callable_one_ s;};

    gamma_distribution(T k_, callable_one_ const &)
      : k(k_)
    {
      EVE_ASSERT(all(is_gtz(k) && is_finite(k)), "k must be strictly positive and finite");
    }

    gamma_distribution(parameters const & p)
      : k(p.k)
    {
      EVE_ASSERT(all(is_gtz(k) && is_finite(k)), "k must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() noexcept
    {
      return { .k = k, .theta = one };
    }

    k_type k;
  };

  template<typename T, typename U>  gamma_distribution(T,U) -> gamma_distribution<T,U>;

  template < floating_real_value T>
  struct gamma_distribution<callable_one_, callable_one_, T>
  {
    using is_distribution_t = void;
    using k_type = callable_zero_;
    using theta_type = callable_one_;
    using value_type = T;
    using parameters = struct { callable_one_ m;  callable_one_ s;};


    gamma_distribution(parameters const & ) { }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto d = exponential_distribution_1<value_type>;
      return d(gen, as(R()));
    }

    parameters params() noexcept
    {
      return { .k = one, .theta = one };
    }

    constexpr gamma_distribution( as<T> const&) {}
  };


  template<typename T>  gamma_distribution(as<T> const&) -> gamma_distribution<callable_one_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto gamma_distribution_11 = gamma_distribution<callable_one_, callable_one_, T>(as<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// pdf
   template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , gamma_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(is_gtz(x), d.invgk*pow_abs(x/d.theta, d.k)*exp(-x/d.theta)/x, zero);
      else if constexpr(std::same_as<T, callable_one_> && floating_value<U>)
        return if_else(is_gtz(x), exp(-x/d.theta)/d.theta, zero);
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
        return if_else(is_gtz(x), d.invgk*pow_abs(x, dec(d.k))*exp(-x), zero);
      else
        return  if_else(is_gtz(x), exp(-x), zero);
    }

    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                                 , gamma_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return eve::gamma_p(if_else(is_ltz(x), zero, x/d.theta), d.k);
      }
      else if constexpr(floating_value<U>)
      {
        return -eve::expm1(if_else(is_ltz(x), zero,-x/d.theta));
      }
      else if constexpr(floating_value<T>)
      {
        return  eve::gamma_p(if_else(is_ltz(x), zero, x), d.k);
      }
      else
        return -eve::expm1(if_else(is_ltz(x), zero,-x));
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , gamma_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      auto invsqrt_2pi = V(0.39894228040143267793994605993438186847585863116493);
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return pow_abs(oneminus(d.theta*x), -d.k);
      }
      else if constexpr(floating_value<U>)
      {
        return rec(oneminus(x*d.theta));
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return pow_abs(oneminus(x), -d.k);;
      }
      else
        return rec(oneminus(x));
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , gamma_distribution<T, U, I> const & d
                                 , V const &p ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return gamma_p_inv( p, d.k)*d.theta;
      }
      else if constexpr(std::same_as<T, callable_one_> && floating_value<U>)
      {
        return  -log1p(-p)*d.theta;
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return  inc(gamma_p_inv(p, d.k));
      }
      else
        return  -log1p(-p);
    }

    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  d.k*d.theta;
      else if constexpr (floating_value<T>)
        return d.k;
      else if constexpr (floating_value<U>)
        return d.theta;
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return if_else(d.k > one(as(d.k)), dec(d.k)*d.theta, zero);
      else if constexpr (floating_value<T> && std::same_as<U, eve::callable_one_>)
        return if_else(d.k > one(as(d.k)), dec(d.k), zero);
      else if constexpr (floating_value<U> && std::same_as<T, eve::callable_one_>)
        return zero(as<I>());
      else if constexpr (std::same_as<T, eve::callable_one_> && std::same_as<U, eve::callable_one_>)
        return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U> && floating_value<U>)
        return d.k+eve::log(d.theta)+ log_abs_gamma(d.k)+oneminus(d.k)*digamma(d.k);
      else if constexpr (floating_value<T>)
        return d.k+ log_abs_gamma(d.k)+oneminus(d.k)*digamma(d.k);
      else if constexpr (floating_value<U>)
        return inc(eve::log(d.theta));
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>)
        return 2/eve::sqrt(d.k);
      else
        return I(2);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>)
        return 6/d.k;
      else
        return I(6);
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  d.k*sqr(d.theta);
      else if constexpr (floating_value<T>)
        return d.k;
      else if constexpr (floating_value<U>)
        return sqr(d.theta);
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , gamma_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  eve::sqrt(d.k)*d.theta;
      else if constexpr (floating_value<T>)
        return  eve::sqrt(d.k);
      else if constexpr (floating_value<U>)
        return d.theta;
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// confidence
    template<typename T, typename U, floating_real_value R
             , floating_real_value V, floating_real_value A,  typename I = T>
    EVE_FORCEINLINE  auto confidence_(EVE_SUPPORTS(cpu_)
                                     , gamma_distribution<T,U,I> const & d
                                     , R const & p
                                     , std::array<V, 4> const & pcov
                                     , A const & alpha ) noexcept
    {
      using v_t = typename normal_distribution<T,U,I>::value_type;
      auto z = cdf(d, p);
      auto l = eve::log(p/(1-p));
      auto dp = rec(p*(1-p));
      auto k = one(as<I>());
      if constexpr(floating_real_value<T>) k = d.k;
      auto dgamma_p = [](auto x, auto k){ return exp(dec(k) * log(x) - x - log_abs_gamma(k));};
      auto da = dgamma_p(z, k)* dp;
      R db;
      if constexpr(floating_real_value<U> && floating_real_value<T>)
        db = eve::exp(k*eve::log(z)-z-eve::log_abs_gamma(k)+eve::log(d.theta))* dp;
      else if constexpr(floating_real_value<U>)
        db = -eve::exp(k*eve::log(z)-z-eve::log_abs_gamma(k))* dp;
      else if constexpr(floating_real_value<T>)
        db  = -eve::exp(eve::log(z)-z+eve::log(d.theta))* dp;
      else
        db = -eve::exp(eve::log(z)-z)*dp;
      auto varL = fma(da, fma(pcov[0], da,  2*pcov[1]*db),  pcov[2]*sqr(db));
      auto halfwidth = -invcdf(normal_distribution_01<I>, alpha*v_t(0.5))*eve::sqrt(varL);
      auto expllo = exp(l - halfwidth);
      auto explup = exp(l + halfwidth);
      auto plo = expllo/inc(expllo);
      auto pup = explup/inc(explup);
      return kumi::make_tuple(p, plo, pup);
    }
  }
}
