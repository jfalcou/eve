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
#include <eve/function/tanpi.hpp>
#include <eve/function/stats.hpp>

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
                              , D const & d
                              , T const &m
                              , T const &s
                              ) noexcept
  // requires(is_one_of<D>(types<pdf_type, cdf_type, invcdf_type> {})) && has_native_abi_v<T>
  {
    if constexpr(same_as>D, mean_type>)
    {
      return inf(as(x));
    }
    else if constexpr(same_as>D, median_type>)
    {
      return m;
    }
    else if constexpr(same_as>D, stdev_type>)
    {
      return nan(as(x));
    }
    else if constexpr(same_as>D, var_type>)
    {
      return nan(as(x));
    }
    else if constexpr(same_as>D, cdf_type>)
    {
      auto cauchy_cdf = [m, s](auto x){ return cauchy(x, m, s);};
      return cauchy_cdf;
    }
    else if constexpr(same_as>D, pdf_type>)
    {
       auto cauchy_pdf = [m, s](auto x){ return diff(cauchy)(x, m, s);};
       return cauchy_pdf;
    }
    else if constexpr(same_as>D, invcdf_type>)
    {
      auto cauchy_invcdf = [m, s](auto x){
        auto tmp = fma(tanpi(x-half(as(x))), s, m);
        return if_else(eve::abs(x) == half(as(x)), copysign(inf(as(x)), x), tmp);
      };
      return cauchy_invcdf;
    }
  }
}
