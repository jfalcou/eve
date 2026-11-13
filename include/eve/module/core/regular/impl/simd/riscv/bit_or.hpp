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
  template<callable_options O, typename T, width_type N>
  wide<T, N> bit_or_(EVE_REQUIRES(rvv_), O const&, wide<T, N> a, wide<T, N> b) noexcept
  requires rvv_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    constexpr auto tgt = as<i_t>();
    return bit_cast(i_t(__riscv_vor(bit_cast(a, tgt), bit_cast(b, tgt), N)), as(a));
  }
}
