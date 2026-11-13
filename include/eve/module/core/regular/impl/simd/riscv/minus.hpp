//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::_
{
  template<callable_options O, signed_integral_scalar_value T, width_type N>
  wide<T, N> minus_(EVE_REQUIRES(rvv_), O const& o, wide<T, N> v) noexcept
  requires (rvv_abi<abi_t<T, N>> && !O::contains(mod))
  {
    if constexpr (O::contains(saturated)) return minus.behavior(cpu_{}, o, v);
    else                                  return wide<T, N>(__riscv_vneg(v, N));
  }
}
