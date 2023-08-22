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

// There are some explanations
// Here: https://lemire.me/blog/2022/12/19/implementing-strlen-using-sve/
// Or: https://www.stonybrook.edu/commcms/ookami/support/_docs/5%20-%20Advanced%20SVE.pdf
template<relative_conditional_expr C, logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(sve_), C c, L m) noexcept
{
  if constexpr( C::is_complete && !C::is_inverted ) return std::nullopt;
  else if constexpr( has_aggregated_abi_v<L> )
  {
    if constexpr( !C::is_complete ) m = m && sve_true(c, as(m));
    auto [lo, hi] = m.slice();
    auto lo_res   = first_true[ignore_none](lo);
    auto hi_res   = first_true[ignore_none](hi);
    if( lo_res ) return lo_res;
    if( hi_res ) *hi_res += lo.size();
    return hi_res;
  }
  else
  {
    auto c_m = L {sve_true(c, eve::as(m))};

    // We don't need this much but it makes the `no matches` case
    // faster
    if( !svptest_any(c_m, m) ) return std::nullopt;

    // we need to ignore as false
    if constexpr( !C::is_complete ) m = m && c_m;

    eve::as_wide_t<eve::element_type_t<L>> first_true_mask =
        svbrkb_z(sve_true<element_type_t<L>>(), m);
    return count_true(first_true_mask);
  }
}

template<logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(sve_), L m) noexcept
{
  return first_true[ignore_none](m);
}

template<logical_simd_value L>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(sve_), top_bits<L> m) noexcept
{
  return first_true(to_logical(m));
}

}
