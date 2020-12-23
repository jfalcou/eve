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
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/min.hpp>
#include <eve/traits/common_compatible.hpp>


namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(minmag, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    auto aa  = eve::abs(a);
    auto bb  = eve::abs(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(bb, aa), b, eve::min(a, b));
      return if_else(is_not_greater_equal(aa, bb), a, tmp);
    }
    else
    {
      return aa < bb ? a : bb < aa ? b : eve::min(a, b);
    }
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto minmag_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that = D()(minmag)(a0,a1);
    ((that = D()(minmag)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  auto minmag_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that = minmag(a0,a1);
    ((that = minmag(that,args)),...);
    return that;
  }
}
