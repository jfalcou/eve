//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/if_else.hpp>

#include <bitset>

namespace eve::detail
{
//================================================================================================
// Logical to Bits
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_bits(rvv_ const&, logical<wide<T, N>> p) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using uint_type = as_uinteger_t<T>;
  return eve::if_else(p, static_cast<uint_type>(-1), static_cast<uint_type>(0));
}

//================================================================================================
// Logical to Mask
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_mask(rvv_ const&, logical<wide<T, N>> p) noexcept
{
  return bit_cast(p.bits(), as<typename logical<wide<T, N>>::mask_type> {});
}

}
