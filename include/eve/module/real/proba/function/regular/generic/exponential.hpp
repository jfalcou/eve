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
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/module/real/proba/detail/attributes.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/one.hpp>

namespace eve
{
  template < typename T, typename Internal = T>
  struct exponential{};

  template < floating_real_value T>
  struct exponential<T>
  {
    using is_distribution_t = void;
    using lambda_type = T;

    exponential(T lambda_) : lambda(lambda_) {
      EVE_ASSERT(all(is_gtz(lambda) && is_finite(lambda)), "lambda must be strictly positive and finite");
    }
    template < floating_real_value TT>
    requires  std::constructible_from<T, TT>
    exponential(TT lambda_)
      : lambda(T(lambda_))
    {
      EVE_ASSERT(all(is_gtz(lambda) && is_finite(lambda)), "lambda must be strictly positive and finite");
    }

    exponential()    : lambda(T(1))   {}

    lambda_type lambda;
  };


  template<typename T>  exponential(T) -> exponential<T>;

  template < floating_real_value T>
  struct exponential < callable_one_, T>
  {
    using is_distribution_t = void;
    using lambda_type = callable_one_;
    using value_type = T;
    constexpr exponential( as_<T> const&) {}
  };

  template<typename T>  exponential(as_<T> const&) -> exponential<callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto exponential_1 = exponential<callable_one_, T>(as_<T>{});


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , exponential<T, I> const &expo
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
                              , exponential<T, I> const &expo
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
                                 , exponential<T, I> const &expo
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
                              , exponential<T, I> const &expo
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
                               , exponential<T, I> const &expo) noexcept
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
                                 , exponential<T, I> const &expo) noexcept
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
                               , exponential<T, I> const &) noexcept
    {
      return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , exponential<T, I> const &expo) noexcept
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
                                , exponential<T, I> const &expo) noexcept
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
                                   , exponential<T, I> const &) noexcept
    {
      return I(2);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , exponential<T, I> const &) noexcept
    {
      return I(6);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , exponential<T, I> const & expo) noexcept
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
                                 , exponential<T, I> const & expo) noexcept
    {
      if constexpr(floating_value<T>)
        return sqr(rec(expo.lambda));
      else
        return one(as<I>());
    }
  }
}
