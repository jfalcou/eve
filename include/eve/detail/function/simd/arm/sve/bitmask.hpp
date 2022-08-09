//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

#include <bitset>

namespace eve::detail
{
//================================================================================================
// Logical to Bits
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_bits(sve_ const&, logical<wide<T, N>> p) noexcept
{
  using type = typename logical<wide<T, N>>::bits_type;
  using e_t  = element_type_t<type>;

  constexpr auto c = categorize<type>();

  if constexpr( match(c, category::uint8) ) return svdup_u8_z(p, (e_t)-1);
  else if constexpr( match(c, category::uint16) ) return svdup_u16_z(p, (e_t)-1);
  else if constexpr( match(c, category::uint32) ) return svdup_u32_z(p, (e_t)-1);
  else if constexpr( match(c, category::uint64) ) return svdup_u64_z(p, (e_t)-1);
}

//================================================================================================
// Logical to Bits
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_mask(sve_ const&, logical<wide<T, N>> p) noexcept
{
  return bit_cast(p.bits(), eve::as<wide<T, N>>{});
}

}
