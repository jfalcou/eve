//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                abs_(EVE_SUPPORTS(vmx_), wide<T, N> const& v) noexcept
requires ppc_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( match(cat, category::unsigned_) ) return v;
  else if constexpr( match(cat, category::size64_) ) return map(eve::abs, v);
  else return vec_abs(v.storage());
}
}
