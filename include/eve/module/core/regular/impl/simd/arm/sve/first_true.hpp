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
  // Or: https://www.stonybrook.edu/commcms/ookami/support/_docs/5%20-%20Advanced%20SVE.pdf‡
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> m) noexcept
  {
    using L = logical<wide<T, N>>;
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else
    {
      if constexpr (has_aggregated_abi_v<L>)
      {
        if constexpr (!C::is_complete)
        {
          if constexpr (relative_conditional_expr<C>) m = m && sve_true(cx, as(m));
          else                                        m = m && expand_mask(cx, as<L>{});
        }

        auto [lo, hi] = m.slice();
        auto lo_res   = first_true(lo);
        auto hi_res   = first_true(hi);

        if (lo_res) return lo_res;
        if (hi_res) *hi_res += lo.size();

        return hi_res;
      }
      else
      {
        L c_m = m;

        constexpr auto has_inactive_lanes = N::value < fundamental_cardinal_v<T>;

        // Compute the condition mask only if necessary, this gives slightly better codegen.
        // This also masks the inactive lanes of the input.
        if constexpr (!C::is_complete || has_inactive_lanes)
        {
          if      constexpr (relative_conditional_expr<C>) c_m = sve_true(cx, as(m));
          // merge everything right away in this case to eliminate one and instruction
          else if constexpr (has_inactive_lanes)           c_m = m && remove_garbage(expand_mask(cx, as<L>{}));
          else                                             c_m = expand_mask(cx, as<L>{});
        }

        // Merging the two masks after the ptest makes this branch appear earlier in the resulting assembly.
        if (!svptest_any(c_m, m)) return std::nullopt;

        // Unconditional mask merge because we need to mask the inactive lanes of there are any.
        // no-op in the has_inactive_lanes case.
        m = m && c_m;

        // Implicit cast to the underlying vector size required.
        as_wide_t<element_type_t<L>> first_true_mask = svbrkb_z(sve_true<element_type_t<L>>(), m);

        return count_true(first_true_mask);
      }
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const& opts, top_bits<logical<wide<T, N>>> m) noexcept
  {
    return first_true.behavior(current_api, opts, to_logical(m));
  }
}
