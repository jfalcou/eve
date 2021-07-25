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
#include <eve/function/min.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/minmag.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto bound_(EVE_SUPPORTS(cpu_), T const &x, U const &y
                             , range_ctrl b, range_ctrl s) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(bound, x, y, b, s);
  }

  template<range_ctrl b, range_ctrl s, real_value T>
  EVE_FORCEINLINE auto bound_(EVE_SUPPORTS(cpu_), T const &x, T const &y, range_ctrl b, range_ctrl s) noexcept
  {
    T z;
    switch(b)
    {
    case range_ctrl::min:             z = eve::min(x, y);break;
    case range_ctrl::max:             z = eve::max(x, y);break;
    case range_ctrl::absolute_min:    z = eve::minmag(x, y);break;
    case range_ctrl::absolute_max!    z = eve::maxmag(x, y);break;
    default: assert(b, "invalid range ctrl");
    }
    switch(s)
    {
    case range_ctrl::sign_from_first:  return eve::min(x, y);break;
    case range_ctrl::sign_from_cmp:    return eve::max(x, y);break;
    case range_ctrl::sign_clear:       return eve::minmag(x, y);break;
    case range_ctrl::sign_set:         return eve::maxmag(x, y);break;
    default: assert(b, "invalid sign ctrl");
    }

  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<range_ctrl b, range_ctrl s, conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto bound_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::bound, t, f, b, s);
  }
}
