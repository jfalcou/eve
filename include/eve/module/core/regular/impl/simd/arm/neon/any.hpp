//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_64_>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (!match_option<condition_key, O, ignore_none_> || (current_api >= asimd) || ((sizeof(T) * N()) <= 4u))
    {
      return any.behavior(cpu_{}, cx, v);
    }
    else
    {
      using u32x2 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<2>>;

      auto dwords = eve::bit_cast(v, eve::as<u32x2>{});
      return vget_lane_u32(u32x2{vpmax_u32(dwords, dwords)}, 0);
    }
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    using u32x4 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<4>>;
    using u64x2 = typename wide<T, N>::template rebind<std::uint64_t, eve::fixed<2>>;

    if constexpr (C::is_complete && !C::is_inverted) return false;
    // we still have to convert down here, so we can do it before ignore.
    else if constexpr ((eve::current_api < eve::asimd) && (sizeof(T) >= 2))
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved    = eve::convert(v, eve::as<eve::logical<half_e_t>>{});
      
      if constexpr (relative_conditional_expr<C>) return any[cx](halved);
      else
      {
        // When calling first_true with a non-relative mask, we need to expand the mask, convert it
        // then call first_true again with a full logical mask.
        auto m = convert(expand_mask(cx, as(v)), as<logical<half_e_t>>{});
        return any[m](halved);
      }
    }
    else if constexpr (!C::is_complete) return any.behavior(cpu_{}, opts, v);
    else if constexpr (eve::current_api >= eve::asimd)
    {
      // Adapted from https://github.com/dotnet/runtime/pull/75864
      auto mask = bit_cast(v.bits(), as<u32x4>{});
      return bit_cast(u32x4(vpmaxq_u32(mask,mask)), as<u64x2>()).get(0) != 0;
    }
    else // chars, no asimd
    {
      auto dwords = eve::bit_cast(v, eve::as<u32x4>());
      return eve::any[ignore_none](detail::to_logical(dwords));
    }
  }
}
