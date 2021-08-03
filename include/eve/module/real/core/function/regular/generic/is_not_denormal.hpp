//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_denormal_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T> || !platform::supports_denormals)
                                      return true_(eve::as(a));
      else                            return is_eqz(a) || is_not_less(eve::abs(a), smallestposval(eve::as(a)));
    }
    else                              return apply_over(is_not_denormal, a);
  }
  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_not_denormal_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return lmask_op(cond, is_not_denormal, u);
  }}
