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
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    // we still have to convert down here, so we can do it before ignore.
    else if constexpr ((current_api < asimd) && (sizeof(T) >= 2))
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved    = convert(v, as<logical<half_e_t>>{});

      if constexpr(relative_conditional_expr<C>) return first_true[cx](halved);
      else
      {
        // When calling first_true with a non-relative mask, we need to expand the mask, convert it
        // then call first_true again with a full logical mask.
        auto m = convert(expand_mask(cx, as(v)), as<logical<half_e_t>>{});
        return first_true[m](halved);
      }
    }
    else return first_true.behavior(cpu_{}, opts, v);
  }
}
