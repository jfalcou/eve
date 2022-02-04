//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/regular/abs.hpp>
#include <eve/module/arithmetic/regular/is_nez.hpp>
#include <eve/module/arithmetic/regular/is_less.hpp>
#include <eve/module/arithmetic/regular/logical_and.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_denormal_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    if constexpr(!floating_value<T> || !eve::platform::supports_denormals)
    {
      return false_(eve::as<T>());
    }
    else if constexpr(has_native_abi_v<T>)
    {
      return is_nez(a) && (abs(a) < smallestposval(eve::as<T>()));
    }
    else
    {
      return apply_over(is_denormal, a);
    }
  }
  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_denormal_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return logical_mask_op(cond, is_denormal, u);
  }
}
