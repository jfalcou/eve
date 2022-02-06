//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/proba/detail/attributes.hpp>
#include <eve/module/proba/detail/urg01.hpp>
#include <eve/module/proba/regular/normal_distribution.hpp>

namespace eve
{
 template < typename T, typename U, typename Internal = T>
  struct lognormal_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct lognormal_distribution<T, U>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = U;
    using value_type = common_compatible_t<T, U>;
    using parameters = struct { value_type m; value_type s;};

    lognormal_distribution(T m_,  U s_)
      : m(m_), s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    parameters params() const noexcept
    {
      return { .m = m, .s = s };
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto n = normal_distribution(m, s);
      return exp(n(gen, as<R>()));
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value U>
  struct lognormal_distribution<callable_zero_, U>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = U;
    using value_type = U;
    using parameters = struct { callable_zero_ m;  value_type s; };

    lognormal_distribution(callable_zero_ const&, U s_)
      : s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    lognormal_distribution(parameters const & p)
      : s(p.s)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto n = normal_distribution(zero, s);
      return exp(n(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = zero, .s = s };
    }


    s_type s;
  };

  template < floating_real_value T>
  struct lognormal_distribution<T, callable_one_>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = decltype(eve::one);
    using value_type = T;
    using parameters = struct { value_type m; callable_one_ s; };

    lognormal_distribution(T m_, callable_one_ const &)
      : m(m_)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    lognormal_distribution(parameters const & p)
      : m(p.m)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto n = normal_distribution(m, one);
      return exp(n(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = m, .s = one };
    }

    m_type m;
  };

  template<typename T, typename U>  lognormal_distribution(T,U) -> lognormal_distribution<T,U>;

  template < floating_real_value T>
  struct lognormal_distribution<callable_zero_, callable_one_, T>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = callable_one_;
    using value_type = T;
    using parameters = struct { callable_zero_ m; callable_one_ s; };

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      auto n = normal_distribution_01<T>;
      return exp(n(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = zero, .s = one };
    }

    constexpr lognormal_distribution( as<T> const&) {}
  };


  template<typename T>  lognormal_distribution(as<T> const&) -> lognormal_distribution<callable_zero_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto lognormal_distribution_01 = lognormal_distribution<callable_zero_, callable_one_, T>(as<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , lognormal_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      auto [m, s] = d.params();
      if constexpr(floating_value<T> || floating_value<U>)
        return if_else(is_gtz(x), cdf(normal_distribution(m, s), eve::log(x)), zero);
      else
        return if_else(is_gtz(x), cdf(normal_distribution_01<I>, eve::log(x)), zero);
    }

    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , lognormal_distribution<T, U, I> const &d
                              , V const &x ) noexcept
    {
      auto [m, s] = d.params();
      if constexpr(floating_value<T> || floating_value<U>)
        return if_else(is_gtz(x), raw(cdf)(normal_distribution(m, s), eve::log(x)), zero);
      else
        return if_else(is_gtz(x), raw(cdf)(normal_distribution_01<I>, eve::log(x)), zero);
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , lognormal_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      auto [m, s] = d.params();
      if constexpr(floating_value<T> || floating_value<U>)
        return  if_else(is_gtz(x), pdf(normal_distribution(m, s), eve::log(x))/x,  zero);
      else
        return if_else(is_gtz(x), pdf(normal_distribution_01<I>, eve::log(x))/x, zero);
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , lognormal_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      auto [m, s] = d.params();
      if constexpr(floating_value<T> || floating_value<U>)
        return eve::exp(invcdf(normal_distribution(m, s), x));
      else
        return  eve::exp(invcdf(normal_distribution_01<I>, x));
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE auto median_(EVE_SUPPORTS(cpu_)
                                 , lognormal_distribution<T,U,I> const & d) noexcept
    {
      auto [m, s] = d.params();
      if constexpr(floating_value<T> || floating_value<U>)
        return exp(median(normal_distribution(m, s)));
      else
      {
         return I(1.0);
      }
    }


    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , lognormal_distribution<T,U,I> const &d) noexcept
    {
      if constexpr (floating_value<U>)
        return median(d)*exp(sqr(d.s)*half(as<U>()));
      else
      {
        auto sqrte = I(1.64872127070012814684865078781416357165377610071014);
        return median(d)*sqrte;
      }
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , lognormal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U>)
        return median(d)*exp(-sqr(d.s));
      else
      {
        auto inve = I( 0.367879441171442);
        return median(d)*inve;
      }
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , lognormal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U> && floating_value<T>)
      {
        auto s2 = sqr(d.s);
        return eve::expm1(s2)*exp(2*d.m+s2);
      }
      else if constexpr (floating_value<T>) // s = 1
      {
        auto em1 = T(.7182818284590452353602874713526624977572470937);
        return em1*eve::exp(2*d.m+1);
      }
      else if constexpr (floating_value<U>) // m = 0
      {
        auto s2 = sqr(d.s);
        return eve::expm1(s2)*exp(s2);
      }
      else
        return I(4.6707742704716049918701399892223453154230684768519);
    }


    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                   , lognormal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U>)
      {
        auto es2 = exp(sqr(d.s));
        return (es2+2)*sqrt(dec(es2));
      }
      else
        return I(6.1848771386325547948354157320560072900223261742372);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , lognormal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U>)
      {
        auto s2 = sqr(d.s);
        return exp(4*s2)+2*exp(3*s2)+3*exp(2*s2)-6;
      }
      else
        return I(10.936392176311525241658602893749337636307499427378);

    }


    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , lognormal_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename lognormal_distribution<T,U,I>::value_type;
      auto sqrt2pi = v_t(2.50662827463100050241576528481104525300698674061);
      auto sqrt2pie = v_t(4.1327313541224929384693918842998526494455219169913);
      if constexpr (floating_value<U>)
        return eve::log2(d.s*exp(d.m+half(as(d.m)))*sqrt2pi);
      else  if constexpr (floating_value<T>) // s = 1
        return eve::log2(exp(d.m+half(as(d.m)))*sqrt2pi);
      else if constexpr (floating_value<U>) // m = 0
        return eve::log2(d.s*sqrt2pie);
      else
        return eve::log2(sqrt2pie);
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                , lognormal_distribution<T,U,I> const & d) noexcept
    {
      return sqrt(var(d));
    }


    //////////////////////////////////////////////////////
    /// confidence
    template<typename T, typename U, floating_real_value R
             , floating_real_value V, floating_real_value A,  typename I = T>
    EVE_FORCEINLINE  auto confidence_(EVE_SUPPORTS(cpu_)
                                     , lognormal_distribution<T,U,I> const & d
                                     , R const & x
                                     , std::array<V, 4> const & cov
                                     , A const & alpha ) noexcept
    {
      R xx = if_else(is_gtz(x), eve::log(x), zero);
      auto par = d.params();
      auto dn = normal_distribution(par.m, par.s);
      return confidence(dn, xx, cov, alpha);
    }
  }
}
