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
#include <eve/conditional.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{

template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(neon128_),
    O const           & opts,
    logical<wide<T, N>> v0) noexcept requires std::same_as<abi_t<T, N>, arm_64_>
{
  using C = rbr::result::fetch_t<condition_key, O>;
  using u32_2 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<2>>;

  if constexpr( C::is_complete && !C::is_inverted ) return true;
  else if constexpr( !C::is_complete ) return all.behavior(cpu_{}, opts, v0);
  else if constexpr( eve::current_api >= eve::asimd ) return all.behavior(cpu_{}, opts, v0);
  else
  {
    if constexpr( sizeof(T) * N() <= 4u ) return all.behavior(cpu_{}, opts, v0);
    auto cond = opts[condition_key];
    auto dwords = eve::bit_cast(v0.bits(), eve::as<u32_2> {});
    dwords      = vpmin_u32(dwords, dwords);

    std::uint32_t combined = vget_lane_u32(dwords, 0);

    if constexpr( sizeof(T) >= 4 ) return (bool)combined;
    else return !~combined;
  }
}

template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(neon128_),
    O const            & opts,
    logical<wide<T, N>> v0) noexcept requires std::same_as<abi_t<T, N>, arm_128_>
{
  using u32_4 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<4>>;
  using u64_2 = typename wide<T, N>::template rebind<std::uint64_t, eve::fixed<2>>;

  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];

  if constexpr( C::is_complete && !C::is_inverted ) return true;
  // we still have to convert down here, so we can do it before ignore.
  else if constexpr( eve::current_api < eve::asimd && sizeof(T) >= 2 )
  {
    using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
    if constexpr (relative_conditional_expr<C>) 
    {
      return all[cond](eve::convert(v0, eve::as<eve::logical<half_e_t>> {}));
    }
    else
    {
      auto m = expand_mask(cond, as(v0));
      return all(convert(logical_ornot(v0, m), as<logical<half_e_t>>{}));
    }
  }
  else if constexpr( !C::is_complete ) return all.behavior(cpu_{}, opts, v0);
  else if constexpr( eve::current_api >= eve::asimd )
  {
    if constexpr( sizeof(T) == 1 ) return vminvq_u8(v0.bits());
    else if constexpr( sizeof(T) == 2 ) return vminvq_u16(v0.bits());
    else
    {
      // Adapted from https://github.com/dotnet/runtime/pull/75864
      auto mask = bit_cast(v0.bits(), as<u32_4>{});
      return bit_cast(u32_4(vpminq_u32(mask,mask)), as<u64_2>()).get(0) == (std::uint64_t)-1;
    }
  }
  else // chars, no asimd
  {
    auto dwords = eve::bit_cast(v0, eve::as<u32_4>());

    // not the same logic as for uint_32 plain so duplicated.
    return eve::all(dwords == (std::uint32_t)-1);
  }
}
}

