//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/fuzzy/floor.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/next.hpp>
#include <eve/function/fuzzy_decorators.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr T trunc_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , U const &n) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(tolerant(trunc), a0, n);
  }

  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr T trunc_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , [[maybe_unused]] U const &n) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      return copysign(trunc(next(eve::abs(a0), n)), a0);
    }
    else return apply_over(tolerant(trunc), a0, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T trunc_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0
                                    , T const &ct) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(has_native_abi_v<T>)
    {
      return copysign(tolerant(floor)(eve::abs(a0), ct), a0);
    }
    else return apply_over(tolerant(trunc), a0, ct);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T trunc_(EVE_SUPPORTS(cpu_)
                                    , tolerant_type const &
                                    , T const &a0) noexcept
  {
    T e = 3*eps(as(a0));
    return eve::trunc(tolerant_type(), a0, e);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_), C const &cond, tolerant_type const &, U const &t) noexcept
  {
    return mask_op(  cond, tolerant(eve::trunc), t);
  }
}
