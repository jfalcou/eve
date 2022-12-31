//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/module/polynomial/detail/horner_impl.hpp>

namespace eve::detail
{

template<value T0, value... Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
{
  return horner_impl(regular_type(), x, args...);
}

//================================================================================================
//== tuples
//================================================================================================
template<value T0, kumi::product_type Ts>
EVE_FORCEINLINE constexpr auto
horner_(EVE_SUPPORTS(cpu_), T0 x, Ts tup) noexcept
{
  return kumi::apply( [&](auto... m) { return horner(x, m...); }, tup);
}

}
