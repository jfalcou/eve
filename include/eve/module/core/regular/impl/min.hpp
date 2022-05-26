//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/implementation.hpp>
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
    return if_else(a < b, b, a);
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
  template<real_value T0, real_value T1, real_value ...Ts>
  auto min_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(min(r_t(a0),r_t(a1)));
    ((that = min(that,r_t(args))),...);
    return that;
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value T0, real_value T1, real_value ...Ts>
  auto min_(EVE_SUPPORTS(cpu_), C const & cond, T0 a0, T1 a1, Ts... args)
  {
     return mask_op(  cond, eve::min, a0, a1, args...);
  }
}
