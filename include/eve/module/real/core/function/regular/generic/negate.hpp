//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto negate_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires  compatible_values<U, T>
  {
    return arithmetic_call(negate, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  T negate_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(signed_value<T>) {  return a*sign(b); }
    else { return if_else(is_nez(b), a, eve::zero);}
  }
}
