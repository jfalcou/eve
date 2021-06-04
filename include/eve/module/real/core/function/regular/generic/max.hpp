//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  -> decltype(arithmetic_call(max, a, b))
  {
    return arithmetic_call(max, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return if_else(is_less(a, b), b, a);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return apply_over(max, a, b);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto max_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(D()(max)(a0,a1));
    ((that = D()(max)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  auto max_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(max(a0,a1));
    ((that = max(that,args)),...);
    return that;
  }
}
