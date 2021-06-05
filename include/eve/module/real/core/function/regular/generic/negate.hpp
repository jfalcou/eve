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
#include <eve/concept/compatible.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/concepts.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto negate_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  -> decltype(arithmetic_call(negate, a, b))
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
