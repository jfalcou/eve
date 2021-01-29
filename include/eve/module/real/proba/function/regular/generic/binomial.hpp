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
#include <eve/constant/half.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>

namespace eve
{
  template < typename T, typename U, typename Internal = T>
  struct binomial{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct binomial<T, U>
  {
    using is_distribution_t = void;
    using n_type = T;
    using p_type = U;
    using value_type = common_compatible_t<T, U>;

    binomial(T n_,  U p_)
      : n(n_), p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    template < floating_real_value TT,  floating_real_value UU>
    requires  std::constructible_from<T, TT> && std::constructible_from<U, UU>
    binomial(TT n_,  UU p_)
      : n(T(n_)), p(U(p_)), q(oneminus(p))
    {
      EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    template < integral_scalar_value N,  floating_real_value UU>
    requires  std::convertible_to<T, N> && std::constructible_from<U, UU>
    binomial(N n_,  UU p_)
      : n(T(n_)), p(U(p_)), q(oneminus(p))
    {
      EVE_ASSERT(all(is_gtz(n_)), "n must be strictly positive");
      EVE_ASSERT(all(p < one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    template < integral_simd_value N,  floating_real_value UU>
    requires  std::convertible_to<T, N> && std::constructible_from<U, UU>
    binomial(N n_,  UU p_)
      : n(convert(n_, as<element_type_t<T>>())), p(U(p_)), q(oneminus(p))
    {
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    n_type n;
    p_type p, q;
  };

  template < floating_real_value U>
  struct binomial<callable_one_, U>
  {
    using is_distribution_t = void;
    using n_type = callable_one_;
    using p_type = U;
    using value_type = U;

    binomial(callable_one_ const&, U p_)
      : p(p_), q(oneminus(p))
    {
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    template < floating_real_value UU>
    requires  std::constructible_from<U, UU>
    binomial(callable_zero_ const & , UU p_)
      : p(U(p_))
    {
      EVE_ASSERT(all(p <= one(as(p)) && is_gez(p)), "p must be in [0, 1]");
    }

    p_type p, q;
  };

  template < floating_real_value T>
  struct binomial<T, callable_half_>
  {
    using is_distribution_t = void;
    using n_type = T;
    using p_type = callable_half_;
    using value_type = T;

    binomial(T n_, callable_one_ const &)
      : n(n_)
    {
      EVE_ASSERT(all(is_finite(n) && is_gtz(n)), "n must be finite and strictly positive");
    }

    template < floating_real_value TT>
    requires  std::constructible_from<T, TT>
    binomial(TT n_, callable_half_ const &)
      : n(T(n_))
    {
     EVE_ASSERT(all(is_finite(n) && is_gtz(n)), "n must be finite and strictly positive");
    }

    n_type n;
  };

  template<typename T, typename U>  binomial(T,U) -> binomial<T,U>;

  template < floating_real_value T>
  struct binomial<callable_one_, callable_half_, T>
  {
    using is_distribution_t = void;
    using n_type = callable_one_;
    using p_type = callable_half_;
    using value_type = T;
    constexpr binomial( as_<T> const&) {}
  };

  template<typename T>  binomial(as_<T> const&) -> binomial<callable_one_, callable_half_, T>;

  template<floating_real_value T>
  inline constexpr auto bernouilli = binomial<callable_one_, callable_half_, T>(as_<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , binomial<T, U, I> const & d
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
                              , binomial<T, U, I> const & d
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
        return exp2(-d.n)*beta(inc(fk), inc(nmk)*half(as(x)));
      }
      else
        return if_else(is_eqz(x) || (x == one(as(x))), half(as(x)), zero);
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , binomial<T, U, I> const & d
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
                                 , binomial<T,U,I> const & d) noexcept
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
                               , binomial<T,U,I> const &d) noexcept
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
                               , binomial<T,U,I> const & d) noexcept
    {
      return median(d);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , binomial<T,U,I> const & d) noexcept
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
                                   , binomial<T,U,I> const & d ) noexcept
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
                                   , binomial<T,U,I> const & d) noexcept
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
                              , binomial<T,U,I> const & d) noexcept
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
                                , binomial<T,U,I> const & d) noexcept
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
