//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    const auto cx = opts[condition_key];

    logical<wide<T, N>> m;
    if constexpr (relative_conditional_expr<C>) m = sve_true(cx, as(m));
    else                                        m = remove_garbage(expand_mask(cx, as(m)));

    if      constexpr (sizeof(T) == 1) return svcntp_b8(m, v);
    else if constexpr (sizeof(T) == 2) return svcntp_b16(m, v);
    else if constexpr (sizeof(T) == 4) return svcntp_b32(m, v);
    else if constexpr (sizeof(T) == 8) return svcntp_b64(m, v);
  }
}
