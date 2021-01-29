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
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
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

namespace eve
{
 template < typename T, typename U, typename Internal = T>
  struct uniform_real_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct uniform_real_distribution<T, U>
  {
    using is_distribution_t = void;
    using a_type = T;
    using b_type = U;
    using value_type = common_compatible_t<T, U>;

    uniform_real_distribution(T a_,  U b_)
      : a(a_), b(b_)
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
    }

    template < floating_real_value TT,  floating_real_value UU>
    requires  std::constructible_from<T, TT> && std::constructible_from<U, UU>
    uniform_real_distribution(TT a_,  UU b_)
      : a(T(a_)), b(U(b_))
    {
      EVE_ASSERT(all(is_finite(a)), "a must be finite");
      EVE_ASSERT(all(is_finite(b)), "b must be finite");
      EVE_ASSERT(all(a < b)       , "a must be stricty less than b");
    }

    a_type a;
    b_type b;
  };

  template<typename T, typename U>  uniform_real_distribution(T,U) -> uniform_real_distribution<T,U>;

  template < floating_real_value T>
  struct uniform_real_distribution<callable_zero_, callable_one_, T>
  {
    using ib_distribution_t = void;
    using a_type = callable_zero_;
    using b_type = callable_one_;
    using value_type = T;

    constexpr uniform_real_distribution( as_<T> const&) {}
  };


  template<typename T>  uniform_real_distribution(as_<T> const&) -> uniform_real_distribution<callable_zero_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto uniform_real_distribution_01 = uniform_real_distribution<callable_zero_, callable_one_, T>(as_<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V, typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , uniform_real_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    requires compatible_values<V, typename uniform_real_distribution<T, U, I>::value_type>
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(x < d.a, zero, if_else(x > d.b, one(as(x)), (x-d.a)/(d.b-d.a)));
      else
        return if_else(is_ltz(x), zero, if_else(x > one(as(x)), one(as(x)), x));;
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , uniform_real_distribution<T, U, I> const & d
                              , V const &x ) noexcept
    requires compatible_values<V, typename uniform_real_distribution<T, U, I>::value_type>
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else((x < d.a) || (x > d.b), zero, rec(d.b-d.a));
      else
        return if_else(is_ltz(x), zero, if_else(x > one(as(x)), one, x));;
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , uniform_real_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    requires compatible_values<V, typename uniform_real_distribution<T, U, I>::value_type>
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return if_else(is_eqz(x), one(as(x)), (eve::exp(x*d.b)-eve::exp(x*d.a))/(x*(d.b-d.a)));
      else
        return if_else(is_eqz(x), one(as(x)), eve::expm1(x)/x);
    }


    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , uniform_real_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    requires compatible_values<V, typename uniform_real_distribution<T, U, I>::value_type>
    {
      EVE_ASSERT(all(is_gez(x) && x < one(as(x))), " x must be in [0, 1]");
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return lerp(x, d.a, d.b);
      }
      else
        return x;
    }

    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return average(d.a, d.b);
      else
      {
        using v_t = typename uniform_real_distribution<T,U,I>::value_type;
        return half(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                               , uniform_real_distribution<T,U,I> const &d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return d.a;
      else
      {
        using v_t = typename uniform_real_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , uniform_real_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
        return  d.a;
      else
      {
        using v_t = typename uniform_real_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U> && floating_value<T>)
        return eve::log(d.b-d.a);
      else
      {
        using v_t = typename uniform_real_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
      }
    }


    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & ) noexcept
    {
        using v_t = typename uniform_real_distribution<T,U,I>::value_type;
        return zero(as<v_t>());
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & ) noexcept
    {
      using v_t = typename uniform_real_distribution<T,U,I>::value_type;
      return v_t(-1.2);
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & d) noexcept
    {
       using v_t = typename uniform_real_distribution<T,U,I>::value_type;
       auto oneo12 = v_t(8.333333333333333e-02);
       if constexpr (floating_value<U> && floating_value<T>)
         return (d.b-d.a)*oneo12;
       else
         return oneo12;
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , uniform_real_distribution<T,U,I> const & d) noexcept
    {
      using v_t = typename uniform_real_distribution<T,U,I>::value_type;
      auto s1 = v_t(2.886751345948129e-01);
      if constexpr (floating_value<U> && floating_value<T>)
        return s1*(d.b-d.a);
      else
        return s1;
    }
  }
}
