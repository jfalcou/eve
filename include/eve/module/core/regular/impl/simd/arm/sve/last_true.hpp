//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/iota.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using L = logical<wide<T, N>>;
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else if constexpr (has_aggregated_abi_v<L>)
    {
      if constexpr (!C::is_complete) m = m && sve_true(cx, as(m));
      auto [lo, hi] = m.slice();
      auto lo_res   = last_true(lo);
      auto hi_res   = last_true(hi);
      if (lo_res) return lo_res;
      if (hi_res) *hi_res += lo.size();
      return hi_res;
    }
    else
    {
      L c_m;

      if constexpr (relative_conditional_expr<C>) c_m = m && sve_true(cx, as(m));
      else                                        c_m = m && expand_mask(cx, as(m));

      if (!svptest_any(c_m, m)) return std::nullopt;

      using it = make_integer_t<sizeof(T), unsigned>;
      return svmaxv(c_m, eve::iota(as<wide<it, N>>{}));
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(sve_), O const& opts, top_bits<logical<wide<T, N>>> m) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return last_true.behavior(current_api, opts, to_logical(m));
  }
}
