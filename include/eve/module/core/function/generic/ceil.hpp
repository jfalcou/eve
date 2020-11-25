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
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/tolerant.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/eps.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T ceil_(EVE_SUPPORTS(cpu_)
                                   , T const &a0) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      T z = eve::trunc(a0);
      return inc[ z < a0 ](z);
    }
    else return apply_over(ceil, a0);
  }

  template<value T, real_value U>
  EVE_FORCEINLINE constexpr T ceil_(EVE_SUPPORTS(cpu_)
                                   , tolerant_type const &
                                   , T const &a0
                                  ,  U tol) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      return -tolerant(floor)(-a0, tol);
    }
    else return apply_over(tolerant(ceil), a0);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T ceil_(EVE_SUPPORTS(cpu_)
                                   , tolerant_type const &
                                   , T const &a0) noexcept
  {
    return tolerant(ceil)(a0, 3*eps(as(a0)));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto ceil_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::ceil, t);
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto ceil_(EVE_SUPPORTS(cpu_), C const &cond, tolerant_type const &, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, tolerant(eve::ceil), t);
  }
}
