//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE wide<T, N>
svtbl(wide<T, N> x, pattern_t<I...>)
{
  wide<T, N> table {I...};
  if constexpr( std::same_as<T, std::uint64_t> ) return svtbl_u64(x, table);
  else if constexpr( std::same_as<T, std::uint32_t> ) return svtbl_u32(x, table);
  else if constexpr( std::same_as<T, std::uint16_t> ) return svtbl_u16(x, table);
  else return svtbl_u8(x, table);
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(sve_), pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr auto table_idxs =
      idxm::to_pattern<idxm::expand_group<G>(idxm::replace_we(std::array {I...}, eve::na_))>();

  return svtbl(x, table_idxs);
}

}
