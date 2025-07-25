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
  template<relative_conditional_expr C, arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE void store_impl(sve_, C const& cx, wide<T, N> v, Ptr p)
    requires (sve_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
  {
    if constexpr (C::has_alternative) store_common(cpu_{}, cx, v, p);
    else if constexpr (C::is_complete && !C::is_inverted) return;
    else svst1(expand_mask(cx, as<wide<T, N>>{}), unalign(p), v);
  }
}
