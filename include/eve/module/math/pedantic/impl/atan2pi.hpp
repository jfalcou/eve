//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/pedantic/atan2.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{
template<floating_ordered_value T, floating_ordered_value U>
EVE_FORCEINLINE auto
atan2pi_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, U const& b) noexcept
{
  return arithmetic_call(pedantic(atan2pi), a, b);
}

template<floating_ordered_value T>
EVE_FORCEINLINE auto
atan2pi_(EVE_SUPPORTS(cpu_),
         pedantic_type const&,
         T const& a,
         T const& b) noexcept requires has_native_abi_v<T>
{
  return radinpi(pedantic(atan2)(a, b));
}
}
