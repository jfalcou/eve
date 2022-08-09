//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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

template<real_scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
all_(EVE_SUPPORTS(neon128_),
     C const           & cond,
     logical<wide<T, N>> v0) noexcept requires std::same_as<abi_t<T, N>, arm_64_>
{
  using u32_2 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<2>>;

  if constexpr( C::is_complete && !C::is_inverted ) return true;
  else if constexpr( !C::is_complete ) return all_(EVE_RETARGET(cpu_), cond, v0);
  else if constexpr( eve::current_api >= eve::asimd ) return all_(EVE_RETARGET(cpu_), cond, v0);
  else
  {
    if constexpr( sizeof(T) * N() <= 4u ) return all_(EVE_RETARGET(cpu_), cond, v0);

    auto dwords = eve::bit_cast(v0.bits(), eve::as<u32_2> {});
    dwords      = vpmin_u32(dwords, dwords);

    std::uint32_t combined = vget_lane_u32(dwords, 0);

    if constexpr( sizeof(T) >= 4 ) return (bool)combined;
    else return !~combined;
  }
}

template<real_scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
all_(EVE_SUPPORTS(neon128_),
     C const           & cond,
     logical<wide<T, N>> v0) noexcept requires std::same_as<abi_t<T, N>, arm_128_>
{
  using u32_4 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<4>>;

  if constexpr( C::is_complete && !C::is_inverted ) return true;
  // we still have to convert down here, so we can do it before ignore.
  else if constexpr( eve::current_api < eve::asimd && sizeof(T) >= 2 )
  {
    using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
    auto halved    = eve::convert(v0, eve::as<eve::logical<half_e_t>> {});
    return eve::all[cond](halved);
  }
  else if constexpr( !C::is_complete ) return all_(EVE_RETARGET(cpu_), cond, v0);
  else if constexpr( eve::current_api >= eve::asimd )
  {
    if constexpr( sizeof(T) == 1 ) return vminvq_u8(v0.bits());
    else if constexpr( sizeof(T) == 2 ) return vminvq_u16(v0.bits());
    else
    {
      // There is no vminvq_u64, so we use vminvq_u32 for everything bigger.
      auto dwords = eve::bit_cast(v0, eve::as<u32_4> {});
      return vminvq_u32(dwords);
    }
  }
  else // chars, no asimd
  {
    using u32_4 = typename wide<T, N>::template rebind<std::uint32_t, eve::fixed<4>>;
    auto dwords = eve::bit_cast(v0, eve::as<u32_4>());

    // not the same logic as for uint_32 plain so duplicated.
    return eve::all[ignore_none](dwords == static_cast<std::uint32_t>(-1));
  }
}
}
