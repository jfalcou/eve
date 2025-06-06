//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE void store_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> v, Ptr p)
    requires (sve_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (C::has_alternative) store.behavior(cpu_{}, opts, v, p);
    else if constexpr (C::is_complete && !C::is_inverted) return;
    else if constexpr (N::value != expected_cardinal_v<T>)
    {
      auto tgt = as<wide<T, N>>{};
      
      if constexpr (std::same_as<C, ignore_none_>)
      {
        svst1(expand_mask(keep_first(N::value), tgt), unalign(p), bit_cast(v, tgt));
      }
      else
      {
        svst1(expand_mask(cx, tgt) && expand_mask(keep_first(N::value), tgt), unalign(p), bit_cast(v, tgt));
      }
    }
    else
    {
      svst1(expand_mask(cx, as<wide<T, N>>{}), unalign(p), v);
    }
  }
}
