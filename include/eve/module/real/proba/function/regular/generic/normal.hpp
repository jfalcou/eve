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
#include <eve/function/erfc.hpp>
#include <eve/function/erfc_inv.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/sqrt_2o_2.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>

namespace eve
{

  template < floating_real_value T>
  struct normal
  {
    using is_distribution_t = void;

    template < floating_real_value U>
    normal(T m_,  U s_)
      requires  std::convertible_to<T, U>
      : m(m_), s(T(s_))
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template <  floating_real_value U>
    normal(U m_,  T s_)
      requires  std::convertible_to<T, U>
      : m(T(m_)), s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    normal(T m_,  T s_) : m(m_), s(s_){
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    normal(T m_) : m(m_), s(T(1)){
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    normal() : m(T(0)), s(T(1))   {}

    T m, s;
  };


  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , normal<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(cdf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , normal<T> const &d
                              , T const &x ) noexcept
    {
      return half(as(x))*erfc(sqrt_2o_2(as(x))*((d.m-x)/d.s));
    }

    //////////////////////////////////////////////////////
    /// raw cdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , normal<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(raw(cdf), d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , normal<T> const &d
                              , T const &x ) noexcept
    {
      using elt_t =  element_type_t<T>;
      if constexpr(std::same_as<elt_t, float>)
      {
        std::cout << "icitte" << std::endl;
        auto l = eve::abs((x-d.m)/d.s);
        auto k = rec(fma(T(0.2316419f),l,one(as(x))));
        auto w = horn<T
//           , 0x3faa466f   //           1.330274429f,
//           , 0xbfe91eea   //           -1.821255978f,
//           , 0x3fe40778   //           1.781477937f,
//           , 0xbeb68f87   //           -0.356563782f,
//           , 0x3ea385fa   //           0.31938153f

          , 0x3ea385fa   //           0.31938153f
          , 0xbeb68f87   //           -0.356563782f,
          , 0x3fe40778   //           1.781477937f,
          , 0xbfe91eea   //           -1.821255978f,
          , 0x3faa466f   //           1.330274429f,

          >(k);
        auto invsqrt_2pi = T(0.39894228040143267793994605993438186847585863116493);
        w*=k*invsqrt_2pi*eve::exp(-sqr(l)*half(as(x)));
        return if_else(is_gtz(x),oneminus(w),w);
      }
      else return cdf(d, x);
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , normal<T> const &d
                              , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(pdf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                              , normal<T> const &d
                              , T const &x ) noexcept
    {
      auto invsig = rec(d.s);
      auto invsqrt_2pi = T(0.39894228040143267793994605993438186847585863116493);
      return eve::exp(mhalf(as(x))*sqr((x-d.m)*invsig))*invsqrt_2pi*invsig;
}

    //////////////////////////////////////////////////////
    /// mgf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , normal<T> const &d
                                 , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(mgf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , normal<T> const &d
                                 , T const &x ) noexcept
    {
      return eve::exp(d.m*x+sqr(d.s*x)*half(as(x)));
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<floating_value T, floating_value U>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , normal<T> const &d
                                 , U const &x ) noexcept
    requires compatible_values<T, U>
    {
      return arithmetic_call(invcdf, d, x);
    }

    template<floating_value T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , normal<T> const &d
                                 , T const &x ) noexcept
    {
      return fma(-sqrt_2(as(x))*erfc_inv( T(2)*x), d.s, d.m);
    }

    //////////////////////////////////////////////////////
    /// median
    template<floating_value T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                 , normal<T> const &d) noexcept
    {
      return d.m;
    }

    //////////////////////////////////////////////////////
    /// mean
    template<floating_value T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , normal<T> const &d) noexcept
    {
      return d.m;
    }
    //////////////////////////////////////////////////////
    /// mode
    template<floating_value T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , normal<T> const & d) noexcept
    {
      return d.m;
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<floating_value T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & d) noexcept
    {
      auto twopie = T(17.0794684453471341309271017390931489900697770715304);
        return half(as<T>())*log(twopie*sqr(d.s));
    }

    //////////////////////////////////////////////////////
    /// skewness
    template<floating_value T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & ) noexcept
    {
      return T(0);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<floating_value T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & ) noexcept
    {
      return T(0);
    }

    //////////////////////////////////////////////////////
    /// mad
    template<floating_value T>
    EVE_FORCEINLINE  auto mad_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & d) noexcept
    {
      auto sqrt_2o_pi = T(0.79788456080286535587989211986876373695171726232986);
      return d.s*sqrt_2o_pi;
    }

    //////////////////////////////////////////////////////
    /// var
    template<floating_value T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & d) noexcept
    {
      return sqr(d.s);
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & d) noexcept
    {
      return d.s;
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<floating_value T>
    EVE_FORCEINLINE  auto kullback_(EVE_SUPPORTS(cpu_)
                                  , normal<T> const & d1
                                  , normal<T> const & d2 ) noexcept
    {
      auto srap = d1.s/d2.s;
      return half(as<T>())*(dec(sqr(srap)+sqr((d1.m-d2.m)/d2.s))+T(2)*eve::log(srap));
    }

  }
}
