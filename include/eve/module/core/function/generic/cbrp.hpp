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

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mhalf.hpp>

#include <type_traits>


// TODO revision to:
// pedantic will call pedantic fma and fnma
// and the no extrapolation will be obtained through named parameter no_extrap = t

namespace eve::detail
{
  template<floating_real_value T
           , floating_real_value U, floating_real_value V
           , floating_real_value W, floating_real_value X>
  EVE_FORCEINLINE auto cbrp_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &ap
                            , V const &b
                            , W const &bp
                            , X const &t) noexcept
  requires compatible_values<T, U> && compatible_values<T, V> &&
           compatible_values<T, W> && compatible_values<T, X>
  {
    return arithmetic_call(cbrp, a, ap, b, bp, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T cbrp_(EVE_SUPPORTS(cpu_)
                         , T const &a
                         , T const &ap
                         , T const &b
                         , T const &bp
                         , T const & t
                         ) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto tm1 = dec(t);
      auto tm12= sqr(tm1);
      auto t2 =  sqr(t);
      auto h00 = tm12*(2*t+1);
      auto h10 = t*tm12;
      auto h01 = t2*(-2*t+3);
      auto h11 = t2*tm1;
      return fma(h00, a, fma(h10, ap, fma(h01, b, h11*bp)));
    }
    else return apply_over(cbrp, a, ap, b, bp, t);
  }

  ////////////////////////////////////////////////////////////////////////////
  // pedantic/numeric
  template<floating_real_value T
           , floating_real_value U, floating_real_value V
           , floating_real_value W, floating_real_value X, decorator D>
  EVE_FORCEINLINE auto cbrp_(EVE_SUPPORTS(cpu_)
                            , D const &
                            , T const &a
                            , U const &ap
                            , V const &b
                            , W const &bp
                            , X const &t) noexcept
  requires compatible_values<T, U> && compatible_values<T, V> &&
  compatible_values<T, W> && compatible_values<T, X>
  {
    return arithmetic_call(D(cbrp), a, ap, b, bp, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T cbrp_(EVE_SUPPORTS(cpu_)
                         , pedantic_type const &
                         , T const &a
                         , T const &ap
                         , T const &b
                         , T const &bp
                         , T const &t) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto test = is_gez(t) && (t <= one(as(t)));
      return if_else(test, cbrp(a, ap, b, bp, t), allbits);
    }
    else return apply_over(numeric(cbrp), a, ap, b, bp, t);
  }
}
