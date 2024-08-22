//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/arch/riscv/rvv_common_masks.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE auto
combine(rvv_ const&, wide<T, N> l, wide<T, N> h) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using that_t = wide<T, typename N::combined_type>;

  constexpr size_t combined_vl = N::combined_type::value;
  if constexpr( eve::has_aggregated_abi_v<that_t> )
  {
    that_t that;
    that.storage().assign_parts(l, h);
    return that;
  }
  else
  {
    auto           wider_l        = simd_cast(l, as<that_t> {});
    auto           wider_h        = simd_cast(h, as<that_t> {});
    constexpr auto shift_size     = N::value;
    that_t         wider_h_placed = __riscv_vslideup(wider_h, wider_h, shift_size, combined_vl);
    auto           mask_all_ones  = rvv_true<T, N>();
    auto           wider_mask     = simd_cast(mask_all_ones, as<logical<that_t>> {});
    return if_else(wider_mask, wider_l, wider_h_placed);
  }
}

template<typename T, typename N>
EVE_FORCEINLINE auto
combine(rvv_ const&, logical<wide<T, N>> l, logical<wide<T, N>> h) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr size_t combined_vl = N::combined_type::value;
  using that_t                 = logical<wide<T, typename N::combined_type>>;

  if constexpr( eve::has_aggregated_abi_v<that_t> )
  {
    that_t that;
    that.storage().assign_parts(l, h);
    return that;
  }
  else
  {
    // TODO: optimize
    return to_logical(eve::combine(l.mask(), h.mask()));
  }
}
}
