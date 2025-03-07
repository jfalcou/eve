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
  template<callable_options O, conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(sve_), C const& cond, O const&, logical<wide<T,N>> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto const m = cond.mask(as<wide<T, N>>{});

    if      constexpr (sizeof(T) == 1) return svcntp_b8(m, v);
    else if constexpr (sizeof(T) == 2) return svcntp_b16(m, v);
    else if constexpr (sizeof(T) == 4) return svcntp_b32(m, v);
    else if constexpr (sizeof(T) == 8) return svcntp_b64(m, v);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T,N>> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return count_true_(EVE_TARGETS(sve_), ignore_none, opts, v);
  }
}
