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

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_or_(EVE_REQUIRES(sve_), O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    // no svorr_x for floating point types
    using i_t = wide<as_integer_t<T, signed>, N>;
    constexpr auto tgt = as<i_t>();
    return bit_cast(i_t(svorr_x(expand_mask(keep_first(N::value), tgt), bit_cast(a, tgt), bit_cast(b, tgt))), as(a));
  }

  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_or_(EVE_REQUIRES(sve_), C& cx, O const&, wide<T, N> a, wide<T, N> b) noexcept
    requires (sve_abi<abi_t<T, N>> && !C::has_alternative)
  {
    // no svorr_m for floating point types
    using i_t = wide<as_integer_t<T, signed>, N>;
    constexpr auto tgt = as<i_t>();
    return bit_cast(i_t(svorr_m(expand_mask(cx, tgt), bit_cast(a, tgt), bit_cast(b, tgt))), as(a));
  }
}
