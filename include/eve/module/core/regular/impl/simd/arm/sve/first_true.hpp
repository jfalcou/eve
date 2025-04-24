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
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> m) noexcept
  {
    using L = logical<wide<T, N>>;
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else
    {
      L c_m = m;

      // Compute the condition mask only if necessary, this gives slightly better codegen.
      if constexpr (!C::is_complete)
      {
        if constexpr (relative_conditional_expr<C>) c_m = sve_true(cx, as(m));
        else                                        c_m = expand_mask(cx, as<L>{});
      }

      if constexpr (has_aggregated_abi_v<L>)
      {
        if constexpr (!C::is_complete) m = m && c_m;

        auto [lo, hi] = m.slice();
        auto lo_res   = first_true(lo);
        auto hi_res   = first_true(hi);
        
        if (lo_res) return lo_res;
        if (hi_res) *hi_res += lo.size();

        return hi_res;
      }
      else
      {
        // Merging the two masks after the ptest makes this branch appear earlier in the
        // resulting assembly.
        if (!svptest_any(c_m, m)) return std::nullopt;
        if constexpr (!C::is_complete) m = m && c_m;

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

