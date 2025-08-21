//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE wide<T, typename N::combined_type>
                combine(rvv_ const&, wide<T, N> l, wide<T, N> h) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using that_t = wide<T, typename N::combined_type>;

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
    constexpr size_t combined_vl    = N::combined_type::value;
    that_t         wider_h_placed = __riscv_vslideup(wider_h, wider_h, shift_size, combined_vl);
    // TODO: can be optimized when simd_cast will support conversions wide<->logical
    logical<that_t> mask([shift_size](auto i, auto) { return i < shift_size; });
    return __riscv_vmerge(wider_h_placed, wider_l, mask, combined_vl);
  }
}

template<typename T, typename N>
EVE_FORCEINLINE logical<wide<T, typename N::combined_type>>
combine(rvv_ const&, logical<wide<T, N>> l, logical<wide<T, N>> h) noexcept
requires rvv_abi<abi_t<T, N>>
{
  using that_t = logical<wide<T, typename N::combined_type>>;
  if constexpr( eve::has_aggregated_abi_v<that_t> )
  {
    that_t that;
    that.storage().assign_parts(l, h);
    return that;
  }
  else
  {
    // TODO: optimize
    return to_logical(combine(current_api, l.mask(), h.mask()));
  }
}
}
