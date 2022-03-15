//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto atan2_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(atan2, a, b);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                             , T const &a0
                             , T const &a1
                             ) noexcept

  requires  has_native_abi_v<T>
  {
    auto q = eve::abs(a0/a1);
    auto z = detail::atan_kernel(q, eve::rec(q));
    return if_else(is_positive(a1), z, (pi(eve::as(a0))-z))*signnz(a0);
  }
}
