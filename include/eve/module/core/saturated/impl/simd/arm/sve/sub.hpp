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
template<scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
sub_(EVE_SUPPORTS(sve_), saturated_type const&, wide<T, N> const& a, wide<T, N> const& b) noexcept
requires sve_abi<abi_t<T, N>>
{
  if constexpr( std::integral<T> ) return svqsub(a, b);
  else return sub(a, b);
}
}
