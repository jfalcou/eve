//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
to_bits(sve_ const&, logical<wide<T, N>> p) noexcept requires sve_abi<abi_t<T, N>>
{
  using type = typename logical<wide<T, N>>::bits_type;
  using e_t  = element_type_t<type>;

        if constexpr( sizeof(T) == 1 ) return type{svdup_u8_z (p, (e_t)-1)};
  else  if constexpr( sizeof(T) == 2 ) return type{svdup_u16_z(p, (e_t)-1)};
  else  if constexpr( sizeof(T) == 4 ) return type{svdup_u32_z(p, (e_t)-1)};
  else  if constexpr( sizeof(T) == 8 ) return type{svdup_u64_z(p, (e_t)-1)};
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
