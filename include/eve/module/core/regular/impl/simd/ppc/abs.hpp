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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> const& v) noexcept requires ppc_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if      constexpr(O::contains(saturated))            return abs_(EVE_TARGETS(cpu_), opts, v);
    else if constexpr( match(cat, category::unsigned_)  ) return v;
    else if constexpr( match(cat, category::size64_)    ) return map_pt(as<wide<T, N>>{}, eve::abs, v);
    else                                                  return vec_abs(v.storage());
  }
}
