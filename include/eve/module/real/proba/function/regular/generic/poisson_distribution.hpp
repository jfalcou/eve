//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
#include <eve/module/real/proba/detail/urg01.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/div.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/gamma_p.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>

namespace eve
{
  template < typename T, typename Internal = T>
  struct poisson_distribution{};

  template < floating_real_value T>
  struct poisson_distribution<T, T>
  {
    using is_distribution_t = void;
    using lambda_type = T;
    using value_type = T;

    poisson_distribution(T lambda_) : lambda(lambda_), expmlambda(eve::exp(-lambda)){
      EVE_ASSERT(all(is_gtz(lambda) && is_finite(lambda)), "lambda must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      if (lambda < value_type(10))
      {
        R p(expmlambda);
        R x(zero(as<R>()));
        auto u = detail::urg01(gen, as<R>());
        auto t = u > p;
        while(any(t)) {
          u = sub[t](u, p);
          x = inc[t](x);
          p = if_else(t, lambda*p/x, p);
          t = u > p;
        }
        return x;
      }
      else
      {
        R k(R(0));
        auto p=detail::urg01(gen, as<R>());
        auto t = p>expmlambda;
        while (any(t))
        {
          p = mul[t](p, detail::urg01(gen, as<R>()));
          k = inc[t](k);
          t = p>expmlambda;
        }
        return k;
      }
    }


    lambda_type lambda;
    lambda_type expmlambda;


  };


  template<typename T>  poisson_distribution(T) -> poisson_distribution<T>;


  template < floating_real_value T>
  struct poisson_distribution < callable_one_, T>
  {
    using is_distribution_t = void;
    using lambda_type = callable_one_;
    using value_type = T;
    using elt_t = element_type_t<T>;

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto p = R(expm1);
      R x(zero(as<R>()));
      auto u = detail::urg01(gen, as<R>());
      auto t = u > p;
      while(any(t)) {
        u = sub[t](u, p);
        x = inc[t](x);
        p = div[t](p, x);
        t = u > p;
      }
      return x;
    }
    constexpr poisson_distribution( as<T> const&) {}
    static constexpr elt_t expm1 = elt_t(0.36787944117144232159552377016146086744581113103176);

  };

  template<typename T>  poisson_distribution(as<T> const&) -> poisson_distribution<callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto poisson_distribution_1 = poisson_distribution<callable_one_, T>(as<T>{});

  namespace detail
  {

    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , poisson_distribution<T, I> const &d
                              , U const &x ) noexcept
    {
      U l = one(as<U>());
      if constexpr(floating_real_value<T>) l = U(d.lambda);
      auto tmp = gamma_p(floor(x+1), l);
      return if_else(is_flint(x) && is_gez(x), tmp, zero);
    }

    //////////////////////////////////////////////////////
    /// pmf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                              , poisson_distribution<T, I> const &d
                              , U const &x ) noexcept
    {
      if constexpr(floating_value<T>)
        return if_else(is_flint(x) && is_gez(x)
                      , d.expmlambda*pow_abs(d.lambda, x)/tgamma(inc(x))
                      , zero);
      else
       return if_else(is_flint(x) && is_gez(x)
                     , rec(tgamma(inc(x)))
                      , zero);
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                              , poisson_distribution<T, I> const &d
                              , U const &t ) noexcept
    {
      if constexpr(floating_value<T>)
        return eve::exp(d.lambda*expm1(t));
      else
        return eve::exp(expm1(t));
    }

    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , poisson_distribution<T, I> const &d) noexcept
    {
      if constexpr(floating_value<T>)
        return d.lambda;
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , poisson_distribution<T, I> const &d) noexcept
    {
      if constexpr(floating_value<T>)
        return floor(d.lambda + T(1/3.0) - T(0.02/d.lambda));  //approximate (exact for integral lambda)
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , poisson_distribution<T, I> const & d) noexcept
    {
      if constexpr(floating_value<T>)
        return if_else(is_flint(d.lambda), dec(d.lambda), floor(d.lambda));
      else
        return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                              , poisson_distribution<T, I> const &d) noexcept
    {
      if constexpr(floating_value<T>)
        return d.lambda;
      else
        return one(as<I>());
    }


    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                , poisson_distribution<T, I> const &d) noexcept
    {
      if constexpr(floating_value<T>)
        return eve::sqrt(d.lambda);
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , poisson_distribution<T, I> const & d) noexcept
    {
     if constexpr(floating_value<T>)
       return rsqrt(d.lambda);
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , poisson_distribution<T, I> const & d) noexcept
    {
      if constexpr(floating_value<T>)
       return rec(d.lambda);
      else
        return one(as<I>());
    }
  }
}
