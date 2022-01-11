//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/all.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/normal_distribution.hpp>
#include <eve/module/proba/detail/attributes.hpp>
#include <eve/module/proba/detail/urg01.hpp>
#include <eve/platform.hpp>
#include <concepts>
#include <type_traits>

namespace eve
{
 template < typename T, typename U, typename Internal = T>
  struct ev_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct ev_distribution<T, U>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = U;
    using value_type = common_compatible_t<T, U>;
    using parameters = struct { value_type m; value_type s;};

    ev_distribution(T m_,  U s_)
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
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value U>
  struct ev_distribution<callable_zero_, U>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = U;
    using value_type = U;
    using parameters = struct { callable_zero_ m;  value_type s; };

    ev_distribution(callable_zero_ const&, U s_)
      : s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    ev_distribution(parameters const & p)
      : s(p.s)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = zero, .s = s };
    }


    s_type s;
  };

  template < floating_real_value T>
  struct ev_distribution<T, callable_one_>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = decltype(eve::one);
    using value_type = T;
    using parameters = struct { value_type m; callable_one_ s; };

    ev_distribution(T m_, callable_one_ const &)
      : m(m_)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    ev_distribution(parameters const & p)
      : m(p.m)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = m, .s = one };
    }

    m_type m;
  };

  template<typename T, typename U>  ev_distribution(T,U) -> ev_distribution<T,U>;

  template < floating_real_value T>
  struct ev_distribution<callable_zero_, callable_one_, T>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = callable_one_;
    using value_type = T;
    using parameters = struct { callable_zero_ m; callable_one_ s; };

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return invcdf(*this, detail::urg01(gen, as<R>()));
    }

    parameters params() const noexcept
    {
      return { .m = zero, .s = one };
    }

    constexpr ev_distribution( as<T> const&) {}
  };


  template<typename T>  ev_distribution(as<T> const&) -> ev_distribution<callable_zero_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto ev_distribution_01 = ev_distribution<callable_zero_, callable_one_, T>(as<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , ev_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return -expm1(-exp((x-d.m)/d.s));
      else if constexpr(floating_value<U>)
        return -expm1(-exp(x/d.s));
      else if constexpr(floating_value<T>)
        return -expm1(-exp(x-d.m));
      else
        return -expm1(-exp(x));
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , ev_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        auto invs =  rec(d.s);
        auto red = exp((x-d.m)*invs);
        return red*exp(-red)*invs;
      }
      else if constexpr(floating_value<U>)
      {
        auto invs =  rec(d.s);
        auto red = exp(x*invs);
        return red*exp(-red)*invs;

      }
      else if constexpr(floating_value<T>)
      {
        auto red = exp(x-d.m);
        return red*exp(-red);
      }
      else
      {
        auto red = exp(x);
        return red*exp(-red);
      }
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , ev_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return fma(log(-log1p(-x)), d.s, d.m);
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
      {
        return log(-log1p(-x))*d.s;
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return log(-log1p(-x))+d.m;
      }
      else
        return log(-log1p(-x));
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      v_t mll2 = v_t(3.665129205816643e-01);
      if constexpr (floating_value<T>)
        return  fma(d.s, mll2, d.m);
      else if constexpr (floating_value<U>)
        return  d.s* mll2;
      else if constexpr (floating_value<T>)
        return mll2+d.m;
      else
        return mll2;
    }


    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , ev_distribution<T,U,I> const &d) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      v_t gamma(0.57721566490153286);
      if constexpr (floating_value<T>)
        return  fma(d.s, gamma, d.m);
      else if constexpr (floating_value<U>)
        return  d.s* gamma;
      else if constexpr (floating_value<T>)
        return gamma+d.m;
      else
        return gamma;
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , ev_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>)
        return d.m;
      else
        return T{}(as<typename ev_distribution<T,U,I>::value_type>());
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      v_t igamma = T(1.57721566490153286);
      if constexpr (floating_value<U>)
        return log(d.s)+igamma;
      else
        return igamma;
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & ) noexcept
    {
      return I(1.13954709940464865749279301890499273124112364236172);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & ) noexcept
    {
      return I(2.4);
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      v_t pi2o6(1.644934066848226436472415166646025189218949901206);
      if constexpr (floating_value<U>)
        return sqr(d.s)*pi2o6;
      else
        return pi2o6;
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , ev_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      v_t sqrtpi2o6(1.2825498301618640955440363596710064114672606675640);
      if constexpr (floating_value<U>)
        return d.s*sqrtpi2o6;
      else
        return sqrtpi2o6;
    }

    //////////////////////////////////////////////////////
    /// confidence
    template<typename T, typename U, floating_real_value R
             , floating_real_value V, floating_real_value A,  typename I = T>
    EVE_FORCEINLINE  auto confidence_(EVE_SUPPORTS(cpu_)
                                     , ev_distribution<T,U,I> const & d
                                     , R const & x
                                     , std::array<V, 4> const & cov
                                     , A const & alpha ) noexcept
    {
      using v_t = typename ev_distribution<T,U,I>::value_type;
      R z = x;
      auto normz = -invcdf(normal_distribution_01<I>, alpha*v_t(0.5));
      auto halfwidth = normz;
      if constexpr(floating_real_value<T> && floating_real_value<U>)
        z = (z-d.m)/d.s;
      else if constexpr(floating_real_value<T>)
        z -= d.m;
      else if constexpr(floating_real_value<U>)
        z /= d.s;
      auto zvar = fma(fma(cov[3], z, 2*cov[1]), z, cov[0]);
      halfwidth *= eve::sqrt(zvar);
      if constexpr(floating_real_value<U>)
        halfwidth /= d.s;
      auto d01 =  ev_distribution_01<I>;
      return kumi::make_tuple(cdf(d01, z), cdf(d01, z-halfwidth), cdf(d01, z+halfwidth));
    }
  }
}
