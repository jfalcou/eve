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
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/real/proba/detail/attributes.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_not_flint.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/lerp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/half.hpp>
#include <concepts>
#include <random>

namespace eve
{
  template < typename T, typename U
             , typename V = common_compatible_floating_elt_t<T, U>>
  struct uniform_discrete_distribution{};

  template < typename T, typename U, typename V >
  requires  compatible_values<T, U>
  struct uniform_discrete_distribution<T, U, V> //: uniform_discrete_distribution_base < T, U, V>
  {
    using is_distribution_t = void;
    using discrete_t = void;
    using a_type = T;
    using b_type = U;
    using elt_t  = V;
    using i_t    = common_compatible_t<T, U>;
    using value_type = std::conditional_t< scalar_value<i_t>, V, wide<V, cardinal_t<i_t>>>;

    uniform_discrete_distribution(T a_,  U b_)
      : a(convert(a_, as<elt_t>())), b(convert(b_, as<elt_t>())), n(inc(b-a))
    {
      check_constraints();
    }

    uniform_discrete_distribution(T a_,  U b_, V)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>())), n(inc(b-a))
    {
      check_constraints();
    }

    uniform_discrete_distribution(T a_,  U b_, as_<V>)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>())), n(inc(b-a))
    {
      check_constraints();
    }

    void check_constraints()
    {
      EVE_ASSERT(all(is_flint(a)), "a must be flint");
      EVE_ASSERT(all(is_flint(b)), "b must be flint");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      auto  stdu = std::uniform_real_distribution<elt_t>(a, inc(b));
      if constexpr(simd_value<R>)
      {
        return [&]<std::size_t... I>( std::index_sequence<I...>)
        {
          auto v = [&](auto) { return floor(stdu(gen)); };
          return R{ v(I)...};
        }( std::make_index_sequence< cardinal_v<R>>{});
      }
      else if constexpr(scalar_value<R>)
      {
        return floor(stdu(gen));
      }
    }

    value_type a;
    value_type b;
    value_type n;
  };


  template < floating_real_value T>
  struct uniform_discrete_distribution<callable_zero_, callable_one_, T>// : uniform_discrete_distribution_base < T, T, T>
  {
    using is_distribution_t = void;
    using discrete_t = void;
    using a_type = callable_zero_;
    using b_type = callable_one_;
    using value_type = T;
    using elt_t  = element_type_t<T>;

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      auto  stdu = std::uniform_real_distribution<elt_t>(T(0), T(2));
      if constexpr(simd_value<R>)
      {
        return [&]<std::size_t... I>( std::index_sequence<I...>)
        {
          auto v = [&](auto) { return floor(stdu(gen)); };
          return R{ v(I)...};
        }( std::make_index_sequence< cardinal_v<R>>{});
      }
      else if constexpr(scalar_value<R>)
      {
        return floor(stdu(gen));
      }
    }

    constexpr uniform_discrete_distribution() { }
    constexpr uniform_discrete_distribution( as_<T> const&) { }

  };

  template<floating_real_value T, floating_real_value U>  uniform_discrete_distribution(T,U) -> uniform_discrete_distribution<T,U>;
  template<floating_real_value T, floating_real_value U, floating_real_value V>  uniform_discrete_distribution(T,U,V) -> uniform_discrete_distribution<T,U, V>;
  template<floating_real_value T, floating_real_value U, floating_real_value V>  uniform_discrete_distribution(T,U,as_<V>) -> uniform_discrete_distribution<T,U,V>;

  template<integral_value T, integral_value U>  uniform_discrete_distribution(T,U) -> uniform_discrete_distribution<T,U>;
  template<integral_value T, integral_value U, floating_real_value V>  uniform_discrete_distribution(T,U,V) -> uniform_discrete_distribution<T,U, V>;
  template<integral_value T, integral_value U, floating_real_value V>  uniform_discrete_distribution(T,U,as_<V>) -> uniform_discrete_distribution<T,U,V>;

  template<typename T>  uniform_discrete_distribution(T const&) -> uniform_discrete_distribution<callable_zero_, callable_one_, T>;
  template<typename T>  uniform_discrete_distribution(as_<T> const&) -> uniform_discrete_distribution<callable_zero_, callable_one_, as_<T>>;

  template<value T>
  inline constexpr auto uniform_discrete_distribution_01 = uniform_discrete_distribution<callable_zero_, callable_one_, T>();

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf discrete
    template<typename T, typename U, floating_value V, typename I = V>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , uniform_discrete_distribution<T, U, I> const & d
                              , V const &x ) noexcept
     requires compatible_values<V, typename uniform_discrete_distribution<T, U, I>::value_type>
     {
      if constexpr(value<T> && value<U>)
      {
        return inc(floor(x)-d.a)/d.n;
      }

      else
        return inc(floor(x))*half(as(x));
    }

    //////////////////////////////////////////////////////
    /// pmf discrete
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pmf_(EVE_SUPPORTS(cpu_)
                                 , uniform_discrete_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    requires compatible_values<V, typename uniform_discrete_distribution<T, U, I>::value_type>
    {
      if constexpr(value<T> && value<U>)
        return if_else((x < d.a) || (x > d.b) || is_not_flint(x), zero, rec(d.n));
      else
        return if_else(is_ltz(x) || (x > one(as(x))) || is_not_flint(x), zero, half(as(x)));;
    }

    //////////////////////////////////////////////////////
    /// mgf discrete
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , uniform_discrete_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    requires compatible_values<V, typename uniform_discrete_distribution<T, U, I>::value_type>
    {
      if constexpr(value<T> && value<U>)
        return if_else(is_eqz(x), one(as(x)), (eve::exp(x*inc(d.b))-eve::exp(x*d.a))/(d.n*expm1(x)));
      else
        return inc(exp(x))*half(as(x));
    }

    //////////////////////////////////////////////////////
    /// mean  discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                                  , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (value<T> && value<U>)
        return average(d.a, d.b);
      else
      {
        using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
        return half(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// median discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , uniform_discrete_distribution<T,U,I> const &d) noexcept
    {
      if constexpr (value<T> && value<U>)
        return  floor(average(d.a, d.b));
      else
      {
        using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// mode discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (value<T> && value<U>)
        return  d.a;
      else
      {
        using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// entropy discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U> && floating_value<T>)
        return eve::log(d.n);
      else
      {
        using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
        return log_2(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// skewness  discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , uniform_discrete_distribution<T,U,I> const & ) noexcept
    {
        using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
    }

    //////////////////////////////////////////////////////
    /// kurtosis discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                   , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
      return v_t(-1.2)*inc(sqr(d.n))/dec(sqr(d.n));
    }


    //////////////////////////////////////////////////////
    /// var discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
      auto oneo12 = v_t(8.333333333333333e-02);
      if constexpr (value<U> && value<T>)
        return dec(sqr(d.n))*oneo12;
      else
        return I(0.25);
    }

    //////////////////////////////////////////////////////
    /// stdev discrete
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , uniform_discrete_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename uniform_discrete_distribution<T,U,I>::value_type;
      auto s1 = v_t(2.886751345948129e-01);
      if constexpr (value<U> && value<T>)
        return s1*sqrt(dec(sqr(d.n)));
      else
        return I(0.5);
    }
  }
}
