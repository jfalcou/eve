//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<callable_options O, relative_conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(neon128_), C const& cx, O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    // we still have to convert down here, so we can do it before ignore.
    else if constexpr ((eve::current_api < eve::asimd) && (sizeof(T) >= 2))
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved    = eve::convert(v, as<logical<half_e_t>> {});
      return first_true[cx](halved);
    }
    else return first_true.behavior(cpu_{}, opts, v);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    return first_true_(EVE_TARGETS(current_api_type), ignore_none, opts, v);
  }
}
