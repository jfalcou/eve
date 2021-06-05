//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
#include <eve/function/max.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  -> decltype(arithmetic_call(maxmag, a, b))
  {
    return arithmetic_call(maxmag, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    auto aa  = eve::abs(a);
    auto bb  = eve::abs(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(aa, bb), b, eve::max(a, b));
      return if_else(is_not_greater_equal(bb, aa), a, tmp);
    }
    else
    {
      return aa < bb ? b : bb < aa ? a : eve::max(a, b);
    }
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto maxmag_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(D()(maxmag)(a0,a1));
    ((that = D()(maxmag)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> maxmag_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(maxmag(a0,a1));
    ((that = maxmag(that,args)),...);
    return that;
  }
}
