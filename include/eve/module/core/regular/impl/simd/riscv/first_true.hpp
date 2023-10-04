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
template<relative_conditional_expr C, logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(rvv_), C c, L m) noexcept
{
  using e_t      = element_type_t<L>;
  using cardinal = cardinal_t<L>;
  if constexpr( C::is_complete && !C::is_inverted ) return std::nullopt;
  else if constexpr( has_aggregated_abi_v<L> )
  {
    if constexpr( !C::is_complete ) m = m && c.mask(as<typename L::mask_type> {});
    auto [lo, hi] = m.slice();
    auto lo_res   = first_true[ignore_none](lo);
    auto hi_res   = first_true[ignore_none](hi);
    if( lo_res ) return lo_res;
    if( hi_res ) *hi_res += lo.size();
    return hi_res;
  }
  else
  {
    auto mask = c.mask(as<typename L::mask_type> {});
    auto res  = __riscv_vfirst(mask, m, cardinal::value);
    if( res == -1 ) return std::nullopt;
    return res;
  }
}

template<logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(rvv_), L m) noexcept
{
  return first_true[ignore_none](m);
}

template<logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(rvv_), top_bits<L> m) noexcept
{
  return first_true(to_logical(m));
}

}
