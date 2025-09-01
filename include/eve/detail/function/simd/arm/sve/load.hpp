//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/ptr.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE wide<T, N> load_impl(sve_, C const& cx, Ptr p, as<wide<T, N>> tgt) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    auto ptr = arm_ptr_downcast(unalign(p));

    if constexpr (C::has_alternative)
    {
      auto res = load[drop_alternative(cx)](p, tgt);
      return eve::replace_ignored(res, cx, cx.alternative);
    }
    else if constexpr (C::is_complete && !C::is_inverted) return {};
    else if constexpr (C::is_complete && C::is_inverted && N() == expected_cardinal_v<T>)
    {
      return svld1(sve_true<T>(), ptr);
    }
    else return svld1(expand_mask(cx, tgt), ptr);
  }
}
