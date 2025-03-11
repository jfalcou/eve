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
  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const&, C c, logical<wide<T, N>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using L = logical<wide<T, N>>;

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else if constexpr (has_aggregated_abi_v<L>)
    {
      if constexpr (!C::is_complete) m = m && sve_true(c, as(m));

      auto [lo, hi] = m.slice();
      auto lo_res   = first_true(lo);
      auto hi_res   = first_true(hi);

      if (lo_res) return lo_res;
      if (hi_res) *hi_res += lo.size();

      return hi_res;
    }
    else
    {
      auto c_m = L {sve_true(c, eve::as(m))};

      // We don't need this much but it makes the `no matches` case faster
      if (!svptest_any(c_m, m)) return std::nullopt;

      // we need to ignore as false
      if constexpr (!C::is_complete) m = m && c_m;

      as_wide_t<element_type_t<L>> first_true_mask = svbrkb_z(sve_true<element_type_t<L>>(), m);
      return count_true(first_true_mask);
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return first_true_(EVE_TARGETS(current_api_type), ignore_none, opts, m);
  }

  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), C const& cx, O const& opts, top_bits<logical<wide<T, N>>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return first_true_(EVE_TARGETS(current_api_type), cx, opts, to_logical(m));
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const& opts, top_bits<logical<wide<T, N>>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return first_true_(EVE_TARGETS(current_api_type), ignore_none, opts, to_logical(m));
  }
}
