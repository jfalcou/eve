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
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/stats.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/as.hpp>

namespace eve::detail
{

  //  general 3
  template<decorator D, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                               , D & d
                               , T const &x
                               , U const &m
                               , V const &s ) noexcept
  requires compatible_values<T, U> && compatible_values<T, V>
  {
    return arithmetic_call(d(cauchy),x, m, s);
  }

  //  general 2
  template<decorator D, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                               , D & d
                               , T const &x
                               , U const &m ) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(d(cauchy),x, m, one(as(x)));
  }

  //  general 1
  template<decorator D, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto cauchy_(EVE_SUPPORTS(cpu_)
                               , D & d
                               , T const &x ) noexcept
  {
    return arithmetic_call(d(cauchy),x, zero(as(x)), one(as(x)));
  }

  ////////////////////////////////////////////////////////////////////////////
  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , D const &
                              , T const &m
                              , T const &s
                              ) noexcept
  {
    if constexpr(std::same_as<D, mean_type>)
    {
      return inf(as(m));
    }
    else if constexpr(std::same_as<D, median_type>)
    {
      return m;
    }
    else if constexpr(std::same_as<D, scale_type>)
    {
      return s;
    }
    else if constexpr(std::same_as<D, stdev_type>)
    {
      return nan(as(m));
    }
    else if constexpr(std::same_as<D, var_type>)
    {
      return nan(as(m));
    }
    else if constexpr(std::same_as<D, cdf_type>)
    {
      auto cauchy_cdf = [m, s](auto x){ return cauchy(x, m, s);};
      return cauchy_cdf;
    }
    else if constexpr(std::same_as<D, pdf_type>)
    {
       auto cauchy_pdf = [m, s](auto x){ return diff(cauchy)(x, m, s);};
       return cauchy_pdf;
    }
    else if constexpr(std::same_as<D, invcdf_type>)
    {
      auto cauchy_invcdf = [m, s](auto x){
        auto tmp = fma(tanpi(x-half(as(x))), s, m);
        // as x is restricted to [0,  1] limits values at 0 and 1 are properly defined
        tmp = if_else(is_eqz(x), minf(as(x)), tmp);
        tmp = if_else(x == one(as(x)), inf(as(x)), tmp);
        return if_else(is_ltz(x) || x > one(as(x)), allbits, tmp);
      };
      return cauchy_invcdf;
    }
  }

  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , D const & d
                              , T const & m
                              ) noexcept
  {
    return d(cauchy)(m, T(1));
  }

  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto cauchy_( EVE_SUPPORTS(cpu_)
                              , D const & d
                              , as_<T> const &
                              ) noexcept
  {
    return d(cauchy)(T(0), T(1));
  }
}
