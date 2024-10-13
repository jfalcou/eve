//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  bit_reverse_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& v)
    noexcept requires (arm_abi<abi_t<T, N>>)
  {
    if constexpr( current_api >= asimd)
    {
      constexpr auto cat = categorize<wide<T, N>>();
      if      constexpr( cat == category::uint8x16    ) return vrbitq_u8(v);
      else if constexpr( cat == category::uint8x8     ) return vrbit_u8(v);
      else return bit_reverse.behavior(cpu_{}, opts, v);
    }
    else return bit_reverse.behavior(cpu_{}, opts, v);
  }
}
