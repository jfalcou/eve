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
#include <utility>

namespace eve
{

  template < floating_real_value T>
  struct cauchy
  {
    using is_distribution_t = void;

    template < floating_real_value U>
    cauchy(T m_,  U s_)
      requires  std::convertible_to<T, U>
      : m(m_), s(T(s_))
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template <  floating_real_value U>
    cauchy(U m_,  T s_)
      requires  std::convertible_to<T, U>
      : m(T(m_)), s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    cauchy(T m_,  T s_) : m(m_), s(s_){
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    cauchy(T m_) : m(m_), s(T(1)){
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    cauchy() : m(T(0)), s(T(1))   {}

    T m, s;
  };


  namespace detail
  {
   //////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T> const &ca
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(cdf, ca, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T> const &ca
                              , T const &x ) noexcept
    {
      return half(as(x)) + atanpi((x-ca.m)/ca.s);;
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T> const &ca
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(pdf, ca, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , cauchy<T> const &ca
                              , T const &x ) noexcept
    {
      auto xmm = (x-ca.m);
      return ca.s/(pi(as(x))*(sqr(ca.s)+sqr(xmm)));
}

    //////////////////////////////////////////////////////
    /// invcdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T> const &ca
                                 , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(invcdf, ca, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T> const &ca
                                 , T const &x ) noexcept
    {
      auto tmp = fma(tanpi(x-half(as(x))), ca.s, ca.m);
      // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
      tmp = if_else(is_eqz(x), minf(as(x)), tmp);
      tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
      return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
    }

    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T> const &ca) noexcept
    {
      return ca.m;
    }

    //////////////////////////////////////////////////////
    /// scale
    template<floating_value T>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T> const &ca) noexcept
    {
      return ca.s;
    }
    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , cauchy<T> const & ca) noexcept
    {
      return ca.m;
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , cauchy<T> const & ca) noexcept
    {
      return log(4*pi(as(ca.s))*ca.s);
    }

    //////////////////////////////////////////////////////
    /// fisher
    template<floating_value T>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_)
                                 , cauchy<T> const & ca) noexcept
    {
      return rec(2*sqr(ca.s));
    }

  }
}
