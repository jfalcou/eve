//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/fuzzy.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/fuzzy/floor.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
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
  EVE_FORCEINLINE auto ceil_(EVE_SUPPORTS(cpu_), C const &cond, tolerant_type const &, U const &t) noexcept
  {
    return mask_op(  cond, tolerant(eve::ceil), t);
  }
}
