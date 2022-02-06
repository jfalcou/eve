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

namespace eve
{

  template < typename T, typename U
             , typename V = common_compatible_floating_elt_t<T, U> >
  struct uniform_continuous_distribution
  {
    using is_distribution_t = void;
    using continuous_t = void;
    using a_type = T;
    using b_type = U;
    using elt_t  = V;
    using i_t    = common_compatible_t<T, U>;
    using value_type = std::conditional_t< scalar_value<i_t>, V, wide<V, cardinal_t<i_t>>>;

    uniform_continuous_distribution(T a_,  U b_)
      : a(convert(a_, as<elt_t>())), b(convert(b_, as<elt_t>()))
    {
      check_constraints();
    }

    uniform_continuous_distribution(T a_,  U b_, V)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>()))
    {
      check_constraints();
    }

    uniform_continuous_distribution(T a_,  U b_, as<V>)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>()))
    {
      check_constraints();
    }

    void check_constraints()
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return fma(detail::urg01(gen, as<R>()), b-a, a);
    }

    value_type a;
    value_type b;
  };

  template<typename T, typename U>  uniform_continuous_distribution(T,U) -> uniform_continuous_distribution<T,U>;
  template<typename T, typename U, typename V>  uniform_continuous_distribution(T,U,V) -> uniform_continuous_distribution<T,U, V>;
  template<typename T, typename U, typename V>  uniform_continuous_distribution(T,U,as<V>) -> uniform_continuous_distribution<T,U,V>;

  template < floating_real_value T>
  struct uniform_continuous_distribution<callable_zero_, callable_one_, T>
  {
    using is_distribution_t = void;
    using continuous_t = void;
    using a_type = callable_zero_;
    using b_type = callable_one_;
    using value_type = T;
    using elt_t = element_type_t<T>;

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return detail::urg01(gen, as<R>());
    }

    constexpr uniform_continuous_distribution() { }
    constexpr uniform_continuous_distribution( as<T> const&) { }
  };


  template<typename T>  uniform_continuous_distribution(as<T> const&) -> uniform_continuous_distribution<callable_zero_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto uniform_continuous_distribution_01 = uniform_continuous_distribution<callable_zero_, callable_one_, T>();

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf continuous
    template<typename T, typename U, floating_value V, typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , uniform_continuous_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    requires compatible_values<V, typename uniform_continuous_distribution<T, U, I>::value_type>
             && continuous<uniform_continuous_distribution<T, U, I>>
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(x < d.a, zero, if_else(x > d.b, one(as(x)), (x-d.a)/(d.b-d.a)));
      else if constexpr(floating_value<T>)
        return if_else(x < d.a, zero, if_else(x > one(as(x)), one(as(x)), (x-d.a)/oneminus(d.a)));
      else if constexpr(floating_value<U>)
        return if_else(is_ltz(x), zero, if_else(x > d.b, one(as(x)), x/d.b));
      else
        return if_else(is_ltz(x), zero, if_else(x > one(as(x)), one(as(x)), x));;
    }

    //////////////////////////////////////////////////////
    /// pdf continuous
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , uniform_continuous_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    requires compatible_values<V, typename uniform_continuous_distribution<T, U, I>::value_type>
             && continuous<uniform_continuous_distribution<T, U, I>>
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else((x < d.a) || (x > d.b), zero, rec(d.b-d.a));
      else if constexpr(floating_value<T>)
        return if_else(x < d.a || x > one(as(x)), one(as(x)), rec(oneminus(d.a)));
      else if constexpr(floating_value<U>)
        return if_else(is_ltz(x) || x > d.b, one(as(x)), rec(d.b));
      else
        return if_else(is_ltz(x), zero, if_else(x > one(as(x)), one, x));;
    }

    //////////////////////////////////////////////////////
    /// mgf continuous
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , uniform_continuous_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    requires compatible_values<V, typename uniform_continuous_distribution<T, U, I>::value_type>
    && continuous<uniform_continuous_distribution<T, U, I>>    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(is_eqz(x), one(as(x)), (eve::exp(x*d.b)-eve::exp(x*d.a))/(x*(d.b-d.a)));
      else if constexpr(floating_value<T>)
        return if_else(is_eqz(x), one(as(x)), (eve::exp(x)-eve::exp(x*d.a))/(x*oneminus(d.a)));
      else if constexpr(floating_value<U>)
        return if_else(is_eqz(x), one(as(x)), eve::expm1(x*d.b)/(x*d.b));
      else
        return if_else(is_eqz(x), one(as(x)), eve::expm1(x)/x);
    }

    //////////////////////////////////////////////////////
    /// invcdf continuous
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , uniform_continuous_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    requires compatible_values<V, typename uniform_continuous_distribution<T, U, I>::value_type>
    && continuous<uniform_continuous_distribution<T, U, I>>    {
      EVE_ASSERT(all(is_gez(x) && x < one(as(x))), " x must be in [0, 1]");
      if constexpr(floating_value<T> && floating_value<U>)
        return lerp(x, d.a, d.b);
      else if constexpr(floating_value<T>)
        return lerp(x, d.a,  one(as(d.a)));
      else if constexpr(floating_value<U>)
        return lerp(x, zero(as(d.b)), d.b);
      else
        return x;
    }

    //////////////////////////////////////////////////////
    /// mean continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                                  , uniform_continuous_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (value<T> && value<U>)
        return average(d.a, d.b);
      else if constexpr(floating_value<T>)
        return average(d.a, one(as(d.a)));
      else if constexpr(floating_value<U>)
        return d.b*half(as(d.b));
      else
      {
        using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
        return half(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// median continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                               , uniform_continuous_distribution<T,U,I> const &d) noexcept
    requires continuous<uniform_continuous_distribution<T, U, I>>
    {
      if constexpr (floating_value<T>)
        return  d.a;
      else
      {
        using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// mode continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , uniform_continuous_distribution<T,U,I> const & d) noexcept
    {
      return median(d);
    }

    //////////////////////////////////////////////////////
    /// entropy continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , uniform_continuous_distribution<T,U,I> const & d) noexcept
    requires continuous<uniform_continuous_distribution<T, U, I>>
    {
      if constexpr (floating_value<U> && floating_value<T>)
        return eve::log(d.b-d.a);
      else if constexpr(floating_value<T>)
        return eve::log1p(-d.a);
      else if constexpr(floating_value<U>)
        return log(d.b);
      else
      {
        using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// skewness continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , uniform_continuous_distribution<T,U,I> const & ) noexcept
    {
        using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
    }

    //////////////////////////////////////////////////////
    /// kurtosis continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , uniform_continuous_distribution<T,U,I> const & ) noexcept
    requires continuous<uniform_continuous_distribution<T, U, I>>
    {
      using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
      return v_t(-1.2);
    }

    //////////////////////////////////////////////////////
    /// var continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , uniform_continuous_distribution<T,U,I> const & d) noexcept
    requires continuous<uniform_continuous_distribution<T, U, I>>
    {
       using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
       auto oneo12 = v_t(8.333333333333333e-02);
       if constexpr (floating_value<U> && floating_value<T>)
         return sqr(d.b-d.a)*oneo12;
      else if constexpr(floating_value<T>)
        return sqr(oneminus(d.a))*oneo12;
      else if constexpr(floating_value<U>)
        return sqr(d.b)*oneo12;
      else
        return oneo12;
    }

    //////////////////////////////////////////////////////
    /// stdev continuous
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , uniform_continuous_distribution<T,U,I> const & d) noexcept
    requires continuous<uniform_continuous_distribution<T, U, I>>
    {
      using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
      auto s1 = v_t(2.886751345948129e-01);
      if constexpr (floating_value<U> && floating_value<T>)
        return s1*(d.b-d.a);
      else if constexpr(floating_value<T>)
        return s1*oneminus(d.a);
      else if constexpr(floating_value<U>)
        return s1*d.b;
      else
        return s1;
    }
  }
}
