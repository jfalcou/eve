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
#include <eve/concept/value.hpp>
#include <eve/function/all.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/beta.hpp>
#include <eve/function/betainc.hpp>
#include <eve/function/log.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/half.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>

namespace eve
{

  template < floating_real_value T>
  struct binomial
  {
    using is_distribution_t = void;

    template < integral_value U>
    binomial(U n_,  T p_)
      requires  std::convertible_to<T, U>
    : n(n_), p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
      EVE_ASSERT(all(p < one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    binomial(T n_,  T p_)
      : n(n_), p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(is_flint(n_) && is_gtz(n_)), "s must be strictly positive and integral");
     EVE_ASSERT(all(p < one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    T n, p, q;
  };


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , binomial<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(cdf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , binomial<T> const &d
                              , T const &x ) noexcept
    {
      return betainc(d.q, d.n-x, inc(x));
    }

    //////////////////////////////////////////////////////
    /// pmf
    template<floating_value U, floating_value T>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , binomial<T> const &d
                              , U const &k ) noexcept
    {

      auto fk = floor(k);
      auto nmk = d.n-fk;
      auto tmp = pow_abs(d.p, k)*pow_abs(d.q, nmk)*beta(inc(fk), inc(nmk))/inc(d.n);
      return if_else(is_flint(k) && is_gez(k) && (k <= d.n), tmp, zero);
    }

    template<floating_value T, integral_value U>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , binomial<T> const &d
                              , U const &k ) noexcept
    requires compatible_values<T, U>
    {
      return pmf(d, T(k));
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , binomial<T> const &d
                                 , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(mgf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , binomial<T> const &d
                                 , T const &x ) noexcept
    {
      return pow_abs(fma(d.p, eve::exp(x), d.q), d.n);
    }

    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , binomial<T> const &d) noexcept
    {
      return floor(d.p*d.n);
    }

    //////////////////////////////////////////////////////
    /// mean
    template<floating_value T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , binomial<T> const &d) noexcept
    {
      return d.p*d.n;
    }
    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , binomial<T> const & d) noexcept
    {
      return floor(d.p*inc(d.n));
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , binomial<T> const & d) noexcept
    {
      // approximate
      auto twopie = T(17.0794684453471341309271017390931489900697770715304);
      return half(as<T>())*eve::log(twopie*d.n*d.p*d.q); // + ô(1/n)
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<floating_value T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , binomial<T> const & ) noexcept
    {
      return T(0);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<floating_value T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , binomial<T> const & d) noexcept
    {
      auto pq = d.p*d.q;
      return oneminus(6*pq)/(d.n*pq);
    }

    //////////////////////////////////////////////////////
    /// var
    template<floating_value T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , binomial<T> const & d) noexcept
    {
      return sqr(d.n*d.p*d.q);
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , binomial<T> const & d) noexcept
    {
      return sqrt(var(d));
    }
  }
}
