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
  struct cauchy {} ;

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
    requires  std::convertible_to<T, TT> && std::convertible_to<U, UU>
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
  struct cauchy<zero_t, U>
  {
    using is_distribution_t = void;
    using m_type = decltype(zero);
    using s_type = U;
    cauchy(U s_)
      : s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < floating_real_value UU>
      requires  std::convertible_to<U, UU>
    cauchy(UU s_)
      : s(U(s_))
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value T>
  struct cauchy<T, one_t>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = decltype(eve::one);

    cauchy(T m_)
      : m(m_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < floating_real_value TT>
      requires  std::convertible_to<T, TT>
    cauchy(TT m_)
      : m(T(m_))
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value Internal>
  struct cauchy<zero_t, one_t, Internal>
  {
    using is_distribution_t = void;
    using m_type = zero_t;
    using s_type = one_t;
    using value_type = Internal;

    cauchy(){}

    m_type m;
    s_type s;
  };

  template < floating_real_value T> using cauchy_01 = cauchy<zero_t, one_t, T>;

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<floating_real_value T, floating_real_value U,  floating_real_value V>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T, U> const &ca
                              , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      return half(as(x)) + atanpi((x-ca.m)/ca.s);;
    }

    template<floating_real_value U,  floating_real_value V>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<zero_t, U> const &ca
                              , V const &x ) noexcept
    requires compatible_values<U, V>
    {
      return half(as(x)) + atanpi(x/ca.s);;
    }

    template<floating_real_value T,  floating_real_value V>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T, one_t> const &ca
                              , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      return half(as(x)) + atanpi(x-ca.m);;
    }

    template<floating_real_value T, floating_real_value V>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy_01<T> const &
                              , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      return half(as(x)) + atanpi(x);;
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<floating_value T, floating_value U, floating_value V>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T, U> const &ca
                              , V const &x ) noexcept
    requires compatible_values<U, V>
    {
      auto xmm = (x-ca.m);
      return ca.s/(pi(as(x))*(sqr(ca.s)+sqr(xmm)));
    }

    template<floating_value U, floating_value V>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<zero_t, U> const &ca
                              , V const &x ) noexcept
    requires compatible_values<U, V>
    {
      return ca.s/(pi(as(x))*(sqr(ca.s)+sqr(x)));
    }

    template<floating_value T, floating_value V>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T, one_t> const & ca
                              , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      auto xmm = (x-ca.m);
      return rec(pi(as(x))*(inc(sqr(xmm))));
    }
    template<floating_real_value T, floating_real_value V>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy_01<T> const &
                              , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      return  rec(pi(as(x))*(inc(sqr(x))));
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<floating_value T, floating_value U, floating_value V>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, U> const &ca
                                 , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      auto tmp = fma(tanpi(x-half(as(x))), ca.s, ca.m);
      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    template<floating_value U, floating_value V>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const &ca
                                 , V const &x ) noexcept
    requires compatible_values<U, V>
    {
      auto tmp = tanpi(x-half(as(x)))*ca.s;
      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    template<floating_value T, floating_value V>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const &ca
                                 , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      auto tmp = tanpi(x-half(as(x)))+ca.m;
      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    template<floating_value T, floating_value V>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &
                                 , V const &x ) noexcept
    requires compatible_values<T, V>
    {
      auto tmp = tanpi(x-half(as<T>()));
      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    //////////////////////////////////////////////////////
    /// median
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, U> const &ca) noexcept
    {
      return ca.m;
    }

    template<floating_value U>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const &) noexcept
    {
      return zero(as<U>());
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const & ca) noexcept
    {
      return ca.m;
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &) noexcept
    {
      return zero(as<T>());
    }

    //////////////////////////////////////////////////////
    /// scale
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T,U> const &ca) noexcept
    {
      return ca.s;
    }


    template<floating_value U>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const & ca) noexcept
    {
      return ca.s;
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const & ) noexcept
    {
      return one(as<T>());
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &) noexcept
    {
      return one(as<T>());
    }

    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , cauchy<T,U> const & ca) noexcept
    {
      return ca.m;
    }

    template<floating_value U>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const &) noexcept
    {
      return zero(as<U>());
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const & ca) noexcept
    {
      return ca.m;
    }


    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &) noexcept
    {
      return zero(as<T>());
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , cauchy<T,U> const & ca) noexcept
    {
      return log(4*pi(as(ca.s))*ca.s);
    }

    template<floating_value U>
    EVE_FORCEINLINE  auto entropy__(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const & ca) noexcept
    {
      return  log(4*pi(as(ca.s))*ca.s);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto entropy__(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const &) noexcept
    {
      return  T(2.531024246969291);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &) noexcept
    {
      return  T(2.531024246969291);
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T,U> const & ca) noexcept
    {
      return rec(2*sqr(ca.s));
    }

    template<floating_value U>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy<zero_t, U> const & ca) noexcept
    {
      return  rec(2*sqr(ca.s));
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T, one_t> const &) noexcept
    {
      return  T(0.5);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy_01<T> const &) noexcept
    {
      return  T(0.5);
    }
  }
}
