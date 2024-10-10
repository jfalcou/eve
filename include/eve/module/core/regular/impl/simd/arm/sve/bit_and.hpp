//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_and_(EVE_REQUIRES(sve_), O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    // no svand_x for floating point types
    using i_t = wide<as_integer_t<T, signed>, N>;
    constexpr auto tgt = as<i_t>{};
    return bit_cast(i_t(svand_x(sve_true<T>(), bit_cast(a, tgt), bit_cast(b, tgt))), as{a});
  }
}
