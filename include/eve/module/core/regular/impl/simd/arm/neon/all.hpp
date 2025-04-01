//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/wide.hpp>
#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_64_>
  {
    if constexpr (!match_option<condition_key, O, ignore_none_> || (current_api >= asimd) || ((sizeof(T) * N()) <= 4u))
    {
      return all.behavior(cpu_{}, opts, v);
    }
    else
    {
      auto dwords = bit_cast(v.bits(), as<wide<uint32_t, fixed<2>>>{});
      dwords      = vpmin_u32(dwords, dwords);

      std::uint32_t combined = vget_lane_u32(dwords, 0);

      if constexpr (sizeof(T) >= 4) return static_cast<bool>(combined);
      else                          return !~combined;
    }
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_REQUIRES(neon128_), O const& opts, logical<wide<T, N>> v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    using u32x4 = wide<uint32_t, fixed<4>>;
    using u64x2 = wide<uint64_t, fixed<2>>;

    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return true;
    // we still have to convert down here, so we can do it before ignore.
    else if constexpr ((current_api < asimd) && (sizeof(T) >= 2))
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved    = convert(v, as<logical<half_e_t>>{});

      if constexpr (relative_conditional_expr<C>) return all[cx](halved);
      else
      {
        // When calling first_true with a non-relative mask, we need to expand the mask, convert it
        // then call first_true again with a full logical mask.
        auto m = convert(expand_mask(cx, as(v)), as<logical<half_e_t>>{});
        return all[m](halved);
      }
    }
    else if constexpr (!C::is_complete) return all.behavior(cpu_{}, opts, v);
    else if constexpr (current_api >= asimd)
    {
      if      constexpr (sizeof(T) == 1) return vminvq_u8(v.bits());
      else if constexpr (sizeof(T) == 2) return vminvq_u16(v.bits());
      else
      {
        // Adapted from https://github.com/dotnet/runtime/pull/75864
        auto mask = bit_cast(v.bits(), as<u32x4>{});
        return bit_cast(u32x4{ vpminq_u32(mask, mask) }, as<u64x2>{}).get(0) == allbits(as<uint64_t>{});
      }
    }
    else // chars, no asimd
    {
      auto dwords = bit_cast(v, as<u32x4>{});

      // not the same logic as for uint_32 plain so duplicated.
      return all(dwords == allbits(as<uint32_t>{}));
    }
  }
}
