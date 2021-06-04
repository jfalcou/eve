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
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  -> decltype(arithmetic_call(min, a, b))
  {
    return arithmetic_call(min, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return if_else(is_less(b, a), b, a);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return apply_over(min, a, b);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto min_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(D()(min)(a0,a1));
    ((that = D()(min)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  auto min_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(min(a0,a1));
    ((that = min(that,args)),...);
    return that;
  }
}
