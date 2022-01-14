//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/ieee.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/proba/detail/attributes.hpp>
#include <eve/module/proba/detail/urg01.hpp>
#include <eve/function/normal_distribution.hpp>

namespace eve
{
  template < typename T, typename Internal = T>
  struct exponential_distribution{};

  template < floating_real_value T>
  struct exponential_distribution<T>
  {
    using is_distribution_t = void;
    using lambda_type = T;
    using value_type = T;

    exponential_distribution(T lambda_) : lambda(lambda_) {
      EVE_ASSERT(all(is_gtz(lambda) && is_finite(lambda)), "lambda must be strictly positive and finite");
    }
    template < floating_real_value TT>
    requires  std::constructible_from<T, TT>
    exponential_distribution(TT lambda_)
      : lambda(T(lambda_))
    {
      EVE_ASSERT(all(is_gtz(lambda) && is_finite(lambda)), "lambda must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    exponential_distribution()    : lambda(T(1))   {}

    lambda_type lambda;
  };


  template<typename T>  exponential_distribution(T) -> exponential_distribution<T>;

  template < floating_real_value T>
  struct exponential_distribution < callable_one_, T>
  {
    using is_distribution_t = void;
    using lambda_type = callable_one_;
    using value_type = T;

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    constexpr exponential_distribution( as<T> const&) {}
  };

  template<typename T>  exponential_distribution(as<T> const&) -> exponential_distribution<callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto exponential_distribution_1 = exponential_distribution<callable_one_, T>(as<T>{});


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , exponential_distribution<T, I> const &expo
                              , U const &x ) noexcept
    {
      if constexpr(floating_value<T>)
        return -expm1(if_else(is_ltz(x), zero, -x*expo.lambda));
      else
        return -expm1(if_else(is_ltz(x), zero, -x));
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , exponential_distribution<T, I> const &expo
                              , U const &x ) noexcept
    {
      if constexpr(floating_value<T>)
        return expo.lambda*exp(-expo.lambda*x);
      else
        return exp(-x);
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , exponential_distribution<T, I> const &expo
                                 , U const &p ) noexcept
    {
      if constexpr(floating_value<T>)
        return -log1p(-p)/expo.lambda;
      else
        return -log1p(-p);
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , exponential_distribution<T, I> const &expo
                              , U const &t ) noexcept
    {
      if constexpr(floating_value<T>)
        return if_else(t < expo.lambda, expo.lambda/(expo.lambda-t),  allbits);
      else
        return if_else(t <one(as(t)), rec(oneminus(t)),  allbits);
    }

    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , exponential_distribution<T, I> const &expo) noexcept
    {
      if constexpr(floating_value<T>)
        return rec(expo.lambda);
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , exponential_distribution<T, I> const &expo) noexcept
    {
      if constexpr(floating_value<T>)
        return log_2(as<T>())*rec(expo.lambda);
      else
        return log_2(as<I>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , exponential_distribution<T, I> const &) noexcept
    {
      return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , exponential_distribution<T, I> const &expo) noexcept
    {
      if constexpr(floating_value<T>)
        return sqr(rec(expo.lambda));
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                , exponential_distribution<T, I> const &expo) noexcept
    {
      if constexpr(floating_value<T>)
        return rec(expo.lambda);
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , exponential_distribution<T, I> const &) noexcept
    {
      return I(2);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , exponential_distribution<T, I> const &) noexcept
    {
      return I(6);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , exponential_distribution<T, I> const & expo) noexcept
    {
      if constexpr(floating_value<T>)
        return oneminus(log(expo.lambda));
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , exponential_distribution<T, I> const & expo) noexcept
    {
      if constexpr(floating_value<T>)
        return sqr(rec(expo.lambda));
      else
        return one(as<I>());
    }

    template<typename T, floating_real_value R, floating_real_value V
             , floating_real_value A, typename I = T>
    EVE_FORCEINLINE  auto confidence_(EVE_SUPPORTS(cpu_)
                                     , exponential_distribution<T,I> const & d
                                     , R const & x
                                     , V const & pcov
                                     , A const & alpha ) noexcept
    {
      using v_t = typename exponential_distribution<T,I>::value_type;
      R z = if_else(is_ltz(x), zero, x);
      if constexpr(floating_real_value<T>) z*= d.lambda;
      auto normz = -invcdf(normal_distribution_01<I>, alpha*v_t(0.5));
      auto halfwidth = normz*eve::sqrt(pcov);
      if constexpr(floating_real_value<T>) halfwidth *= d.lambda;
      auto exp_halfwidth =  eve::exp(halfwidth);
      return kumi::make_tuple(-expm1(-z), -expm1(-z/exp_halfwidth), -expm1(-z*exp_halfwidth));
    }

  }
}
