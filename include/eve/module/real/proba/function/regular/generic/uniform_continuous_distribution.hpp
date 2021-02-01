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
  template < typename T,  typename U> using common_compatible_floating_t =
    detail::as_floating_point_t<common_compatible_t<T, U>>;
  template < typename T,  typename U> using common_compatible_floating_elt_t =
    element_type_t<common_compatible_floating_t<T, U>>;

  template < typename T, typename U
             , typename Internal = common_compatible_floating_elt_t<T, U> >
  struct uniform_continuous_distribution{};

  template < integral_value T, integral_value U, typename V >
  requires  compatible_values<T, U>
  struct uniform_continuous_distribution<T, U, V>
  {
    using is_distribution_t = void;
    using continuous_t = void;
    using a_type = T;
    using b_type = U;
    using elt_t  = V;
    using i_t    = common_compatible_t<T, U>;
    using value_type = std::conditional_t< scalar_value<i_t>, V, wide<V, cardinal_t<i_t>>>;

    uniform_continuous_distribution(T a_,  U b_)
      : a(convert(a_, as<elt_t>())), b(convert(b_, as<elt_t>())), n(inc(b-a))
    {
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }

    uniform_continuous_distribution(T a_,  U b_, V)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>())), n(inc(b-a))
    {
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }

    uniform_continuous_distribution(T a_,  U b_, as_<V>)
      : a(convert(a_, as<V>())), b(convert(b_, as<V>())), n(inc(b-a))
    {
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }

    void init()
    {
      if constexpr(scalar_value<value_type>)
        stdu = std::uniform_real_distribution<>(a, b);
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      if constexpr(simd_value<R>)
      {
        return [&]<std::size_t... I>( std::index_sequence<I...>)
        {
          auto v = [&](auto) { return stdu(gen); };
          return R{ v(I)...};
        }( std::make_index_sequence< cardinal_v<R>>{});
      }
      else if constexpr(scalar_value<R>)
      {
        return stdu(gen);
      }
    }

    std::uniform_real_distribution<elt_t> stdu;
    value_type a;
    value_type b;
    value_type n;
  };

  template < floating_real_value T, floating_real_value U, typename V>
  requires  compatible_values<T, U>
  struct uniform_continuous_distribution<T, U, V>
  {
    using is_distribution_t = void;
    using continuous_t = void;
    using a_type = T;
    using b_type = U;
    using elt_t  = V;
    using value_type = common_compatible_t<T, U>;

    uniform_continuous_distribution(T a_,  U b_)
      : a(a_), b(b_)
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }
    uniform_continuous_distribution(T a_,  U b_,  V )
      : a(convert(a_, as<elt_t>())), b(convert(b_, as<elt_t>()))
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }
    uniform_continuous_distribution(T a_,  U b_,  as_<V>)
      : a(convert(a_, as<elt_t>())), b(convert(b_, as<elt_t>()))
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
      init();
    }

    void init()
    {
      if constexpr(scalar_value<value_type>)
        stdu = std::uniform_real_distribution<>(a, b);
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      if constexpr(simd_value<R>)
      {
        return [&]<std::size_t... I>( std::index_sequence<I...>)
        {
          auto v = [&](auto) { return stdu(gen); };
          return R{ v(I)...};
        }( std::make_index_sequence< cardinal_v<R>>{});
      }
      else if constexpr(scalar_value<R>)
      {
        return stdu(gen);
      }
    }
    std::uniform_real_distribution<elt_t> stdu;

    value_type a;
    value_type b;
  };

  template<typename T, typename U>  uniform_continuous_distribution(T,U) -> uniform_continuous_distribution<T,U>;
  template<typename T, typename U, typename V>  uniform_continuous_distribution(T,U,V) -> uniform_continuous_distribution<T,U, V>;
  template<typename T, typename U, typename V>  uniform_continuous_distribution(T,U,as_<V>) -> uniform_continuous_distribution<T,U,V>;

  template < floating_real_value T>
  struct uniform_continuous_distribution<callable_zero_, callable_one_, T>
  {
    using is_distribution_t = void;
    using continuous_t = void;
    using a_type = callable_zero_;
    using b_type = callable_one_;
    using value_type = T;
    using elt_t = element_type_t<T>;
    uniform_continuous_distribution()
    {
      init();
    }

    void init()
    {
      if constexpr(scalar_value<value_type>)
        stdu = std::uniform_real_distribution<>(T(0), T(1));
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as_<R> const & )
      requires scalar_value<value_type>
    {
      if constexpr(simd_value<R>)
      {
        return [&]<std::size_t... I>( std::index_sequence<I...>)
        {
          auto v = [&](auto) { return stdu(gen); };
          return R{ v(I)...};
        }( std::make_index_sequence< cardinal_v<R>>{});
      }
      else if constexpr(scalar_value<R>)
      {
        return stdu(gen);
      }
    }
    constexpr uniform_continuous_distribution( as_<T> const&) {}
    std::uniform_real_distribution<elt_t> stdu;
  };


  template<typename T>  uniform_continuous_distribution(as_<T> const&) -> uniform_continuous_distribution<callable_zero_, callable_one_, T>;

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
      {
        return lerp(x, d.a, d.b);
      }
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
      if constexpr (floating_value<T> && floating_value<U>)
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
      if constexpr (value<T> && value<U>)
        return  d.a;
      else
      {
        using v_t = typename uniform_continuous_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
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
      else
        return s1;
    }
  }
}
