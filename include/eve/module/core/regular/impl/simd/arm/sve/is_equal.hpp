//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<callable_options O, typename W>
  EVE_FORCEINLINE as_logical_t<W> is_equal_(EVE_REQUIRES(sve_), O const& opts, W a, W b) noexcept
    requires sve_abi<typename W::abi_type>
  {
    const auto mask = keep_first(W::size()).mask(as(a));

    if      constexpr (logical_simd_value<W>)            return svnot_z(mask, sveor_z(mask, a, b));
    else if constexpr (O::contains_any(almost, numeric)) return is_equal[opts].retarget(cpu_{}, a, b);
    else                                                 return svcmpeq(mask, a, b);
  }

  template<callable_options O, conditional_expr C, typename W>
  EVE_FORCEINLINE as_logical_t<W> is_equal_(EVE_REQUIRES(sve_), C const& cx, O const& opts, W a, W b) noexcept
    requires sve_abi<typename W::abi_type>
  {
    const auto mask = expand_mask(cx, as(a));

    if      constexpr (logical_simd_value<W>)            return svnot_z(mask, sveor_z(mask, a, b));
    else if constexpr (O::contains_any(almost, numeric)) return is_equal[opts][cx].retarget(cpu_{}, a, b);
    else                                                 return svcmpeq(mask, a, b);
  }
}
