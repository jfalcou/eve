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
  // As return by arm.
  using int_type       = as_integer_t<T, unsigned>;
  using u_wide_t       = wide<int_type, N>;
  using u_mask_t       = logical<u_wide_t>;
  auto     u_mask      = bit_cast(p, as<u_mask_t> {});
  u_wide_t if_else_res = if_else(u_mask,
                                 /* True value */ static_cast<int_type>(-1),
                                 /* False Value */ static_cast<int_type>(0));
  return if_else_res;
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
