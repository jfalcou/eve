//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
//================================================================================================
// Logical to Bits
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE typename logical<wide<T, N>>::bits_type
to_bits(rvv_ const&, logical<wide<T, N>> p) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using u_t = as_uinteger_t<T>;
  auto z = wide<u_t, N>(0);
  auto a = allbits(as<wide<u_t, N>>{});

  return __riscv_vmerge_tu(a.storage(), z.storage(), a.storage(), p.storage(), N::value);

//  return eve::if_else(p, static_cast<uint_type>(-1), static_cast<uint_type>(0));
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
