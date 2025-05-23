//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), O const& opts, logical<wide<T, N>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (C::is_complete)
    {
      if constexpr (!C::is_inverted) return 0;
      else return __riscv_vcpop(v, N::value);
    }
    else
    {
      const auto m = expand_mask(opts[condition_key], as<wide<T, N>>{});
      return __riscv_vcpop(m, v, N::value);
    }
  }

  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(rvv_), O const& opts, top_bits<logical<wide<T, N>>> v) noexcept
    requires rvv_abi<abi_t<T, N>>
  {
    return count_true.behavior(current_api, opts, v.storage);
  }
}
