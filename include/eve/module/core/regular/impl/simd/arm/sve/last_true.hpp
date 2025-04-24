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
  {
    using L = logical<wide<T, N>>;
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else
    {
      if constexpr (relative_conditional_expr<C>) m = m && sve_true(cx, as(m));
      else                                        m = m && expand_mask(cx, as(m));

      if constexpr (has_aggregated_abi_v<L>)
      {
        auto [lo, hi] = m.slice();
        auto hi_res   = last_true(hi);
        auto lo_res   = last_true(lo);

        if (hi_res) return *hi_res + lo.size();
        else        return lo_res;
      }
      else
      {
        if (!svptest_any(m, m)) return std::nullopt;

        using it = make_integer_t<sizeof(T), unsigned>;
        return svmaxv(m, eve::iota(as<wide<it, N>>{}));
      }
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(sve_), O const& opts, top_bits<logical<wide<T, N>>> m) noexcept
  {
    return last_true.behavior(current_api, opts, to_logical(m));
  }
}
