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
#include <eve/function/numeric/fma.hpp>

namespace eve::detail
{


  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , numeric_type const &
                                        , T const &x, U const &a, V const &b) noexcept
  requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return numeric(fma)(x, a, b);
  }

  //================================================================================================
  //N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
           EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                                 , numeric_type const &
                                                 , T0 x, T1 a, T2 b, Ts... args) noexcept
{
  using r_t = common_compatible_t<T0, T1, T2, Ts...>;
  auto nhorner = numeric(horner);
  r_t that(nhorner(x, a, b));
  auto next = [x](auto that, auto arg){
    return nhorner(x, that, arg);
  };
  ((that = next(that, args)),...);
  return that;
}
