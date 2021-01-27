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

namespace eve
{

  template < floating_real_value T>
  struct exponential
  {
    using is_distribution_t = void;

    exponential(T l) : lambda(l) {
      EVE_ASSERT(all(is_gtz(l) && is_finite(l)), "lambda must be strictly positive and finite");
    }

    exponential()    : lambda(T(1))   {}

    T lambda;
  };


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return -expm1(if_else(is_ltz(x), zero, -x*expo.lambda));
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return expo.lambda*exp(-expo.lambda*x);
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , exponential<T> const &expo
                                 , U const &p ) noexcept
    requires compatible_values<T, U>
    {
      return -log1p(-p)/expo.lambda;
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(mgf, expo, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo
                              , T const &t ) noexcept
    {
      return if_else(t < expo.lambda, expo.lambda/(expo.lambda-t),  allbits);
    }

    //////////////////////////////////////////////////////
    /// mean
    template<floating_value T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , exponential<T> const &expo) noexcept
    {
      return rec(expo.lambda);
    }


    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , exponential<T> const &expo) noexcept
    {
      return log_2(as<T>())*rec(expo.lambda);
    }

    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , exponential<T> const &) noexcept
    {
      return zero(as<T>());
    }

    //////////////////////////////////////////////////////
    /// var
    template<floating_value T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo) noexcept
    {
      return sqr(rec(expo.lambda));
    }


    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                              , exponential<T> const &expo) noexcept
    {
      return rec(expo.lambda);
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<floating_value T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , exponential<T> const &) noexcept
    {
      return T(2);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<floating_value T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , exponential<T> const &) noexcept
    {
      return T(6);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , exponential<T> const & expo) noexcept
    {
      return oneminus(log(expo.lambda));
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<floating_value T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , exponential<T> const & expo) noexcept
    {
      return sqr(rec(expo.lambda));
    }
  }

  template < floating_real_value T>
  struct exponential_1
  {
    using is_distribution_t = void;

    exponential_1(as_<T> const &)  {}

  };

  namespace detail
  {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // optimzation for static lambda = 1
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , exponential_1<T> const &
                              , U const &x ) noexcept
    {
      return -expm1(if_else(is_ltz(x), zero, -x));
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , exponential_1<T> const &
                              , U const &x ) noexcept
    {
      return exp(-x);
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , exponential_1<T> const &
                                 , U const &p ) noexcept
    {
      return -log1p(-p);
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , exponential_1<T> const &
                              , U const &t ) noexcept
    {
      return if_else(t < one(as<T>()), rec(-t),  allbits);
    }

    //////////////////////////////////////////////////////
    /// mean
    template<floating_value T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , exponential_1<T> const &) noexcept
    {
      return one(as<T>());
    }


    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , exponential_1<T> const &) noexcept
    {
      return log_2(as<T>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , exponential_1<T> const &) noexcept
    {
      return zero(as<T>());
    }

    //////////////////////////////////////////////////////
    /// var
    template<floating_value T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , exponential_1<T> const &) noexcept
    {
      return one(as<T>());
    }


    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                              , exponential_1<T> const &) noexcept
    {
      return  one(as<T>());
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<floating_value T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , exponential_1<T> const &) noexcept
    {
      return T(2);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<floating_value T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , exponential_1<T> const &) noexcept
    {
      return T(6);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , exponential_1<T> const &) noexcept
    {
      return one(as<T>());
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<floating_value T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , exponential_1<T> const &) noexcept
    {
      return one(as<T>());
    }
  }
}
