//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  requires compatible_values<T, U>
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
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::min, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto min_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(min(r_t(a0),r_t(a1)));
    ((that = min(that,r_t(args))),...);
    return that;
  }
}
