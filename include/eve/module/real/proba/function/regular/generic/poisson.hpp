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
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/gamma_p.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_finite.hpp>

namespace eve
{

  template < floating_real_value T>
  struct poisson
  {
    using is_distribution_t = void;

    poisson(T l) : lambda(l), expmlambda(eve::exp(-lambda))  {
      EVE_ASSERT(all(is_gez(l) && is_finite(l)), "lambda must be strictly positive and finite");
    }

    poisson()    : lambda(T(1)), expmlambda(eve::exp(-lambda))  {}

    T lambda;
    T expmlambda;
  };


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(cdf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , T const &x ) noexcept
    {
      auto tmp = gamma_p(floor(x+1), d.lambda);
      return if_else(is_flint(x) && is_gez(x), tmp, zero);
    }

    //////////////////////////////////////////////////////
    /// pmf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(pmf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , T const &x ) noexcept
    {
      return if_else(is_flint(x) && is_gez(x)
                    , d.expmlambda*pow_abs(d.lambda, x)/tgamma(inc(x))
                    , zero);
    }


    //////////////////////////////////////////////////////
    /// mgf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(mgf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d
                              , T const &t ) noexcept
    {
      return eve::exp(d.lambda*expm1(t));
    }

    //////////////////////////////////////////////////////
    /// mean
    template<floating_value T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , poisson<T> const &d) noexcept
    {
      return d.lambda;
    }


    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , poisson<T> const &d) noexcept
    {
      //approximate
      return floor(d.lambda + T(1/3.0) - T(0.02/d.lambda));
    }

    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , poisson<T> const & d) noexcept
    {
      return if_else(is_flint(d.lambda), dec(d.lambda), floor(d.lambda));
    }

    //////////////////////////////////////////////////////
    /// var
    template<floating_value T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , poisson<T> const &d) noexcept
    {
      return d.lambda;
    }


    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                , poisson<T> const &d) noexcept
    {
      return sqrt(d.lambda);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<floating_value T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , poisson<T> const & d) noexcept
    {
      return rec(d.lambda);
    }
    
    //////////////////////////////////////////////////////
    /// skewness
    template<floating_value T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , poisson<T> const & d) noexcept
    {
      return rsqrt(d.lambda);
    }
  }
}
