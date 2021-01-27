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
#include <eve/function/atanpi.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <concepts>

namespace eve
{
  template < typename T, typename U, typename Internal = T>
  struct cauchy{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct cauchy<T, U>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = U;

    cauchy(T m_,  U s_)
      : m(m_), s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < floating_real_value TT,  floating_real_value UU>
    requires  std::constructible_from<T, TT> && std::constructible_from<U, UU>
    cauchy(TT m_,  UU s_)
      : m(T(m_)), s(U(s_))
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value U>
  struct cauchy<callable_zero_, U>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = U;
    cauchy(callable_zero_ const&, U s_)
      : s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < floating_real_value UU>
      requires  std::constructible_from<U, UU>
    cauchy(callable_zero_ const &, UU s_)
      : s(U(s_))
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value T>
  struct cauchy<T, callable_one_>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = decltype(eve::one);

    cauchy(T m_, callable_one_ const &)
      : m(m_)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < floating_real_value TT>
      requires  std::constructible_from<T, TT>
    cauchy(TT m_, callable_one_ const &)
      : m(T(m_))
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value Internal>
  struct cauchy<callable_zero_, callable_one_, Internal>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = callable_one_;
    using value_type = Internal;

    cauchy(){}
    cauchy(callable_zero_ const &, callable_one_ const&){}

    m_type m;
    s_type s;
  };

  template < floating_real_value T> using cauchy_01 = cauchy<callable_zero_, callable_one_, T>;

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, U, I> const & ca
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return half(as(x)) + atanpi((x-ca.m)/ca.s);
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
        return half(as(x)) + atanpi(x/ca.s);
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
        return half(as(x)) + atanpi(x-ca.m);
      else
        return half(as(x)) + atanpi(x);
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, U, I> const & ca
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        auto xmm = (x-ca.m);
        return ca.s/(pi(as(x))*(sqr(ca.s)+sqr(xmm)));
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
        return ca.s/(pi(as(x))*(sqr(ca.s)+sqr(x)));
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        auto xmm = (x-ca.m);
        return rec(pi(as(x))*(inc(sqr(xmm))));
      }
      else
        return  rec(pi(as(x))*(inc(sqr(x))));
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, U, I> const & ca
                                 , V const &x ) noexcept
    {
      using  U1 =   std::conditional_t<bool(floating_value<U>), U, I>;
      using  T1 =   std::conditional_t<bool(floating_value<T>),T, U1>;
      using r_t = common_compatible_t<T1, V>;
      r_t tmp;
      if constexpr(floating_value<T> && floating_value<U>)
        tmp = fma(tanpi(x-half(as(x))), ca.s, ca.m);
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
        tmp = tanpi(x-half(as(x)))*ca.s;
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
        tmp = tanpi(x-half(as(x)))+ca.m;
      else
        tmp = tanpi(x-half(as(x)));

      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                  , cauchy<T,U,I> const & ca) noexcept
    {
      if constexpr (floating_value<T>)
        return  ca.m;
      else if constexpr (floating_value<U>)
        return zero(as<U>());
      else
        return zero(as<I>());
    }


    //////////////////////////////////////////////////////
    /// scale
    template<typename T, typename U, typename I = U>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                , cauchy<T,U,I> const & ca) noexcept
    {
      if constexpr (floating_value<U>)
        return  ca.s;
      else if constexpr (floating_value<T>)
        return one(as<T>());
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = U>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , cauchy<T,U,I> const & ca) noexcept
    {
      return median(ca);
    }


    //////////////////////////////////////////////////////
    /// entropy
    template<typename T,  typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T,U,I> const & ca) noexcept
    {
      if constexpr (floating_value<U>)
        return  log(4*pi(as(ca.s))*ca.s);
      else
        return  I(2.531024246969291);
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<typename T,  typename U,  typename I = T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T,U,I> const & ca) noexcept
    {
      if constexpr (floating_value<U>)
        return rec(2*sqr(ca.s));
      else
        return I(0.5);
    }
  }
}
