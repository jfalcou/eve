//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>
#include "eve/detail/overload.hpp"

namespace eve::detail
{
  // Generate better code on x86 than just comparing to 0
  template<signed_integral_value T, typename N>
  EVE_FORCEINLINE constexpr auto is_ltz_(EVE_SUPPORTS(sse2_), wide<T,N> const& v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t = as_logical_t<wide<T,N>>;
    if constexpr( abi_t<T, N>::is_wide_logical )  return bit_cast(v >> 31, as<l_t>{});
    else                                          return  is_ltz_(EVE_RETARGET(cpu_), v);
  }
}
