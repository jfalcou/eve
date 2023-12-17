//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(sve_), C const& mask, O const&, wide<T, N> const& v) noexcept requires sve_abi<abi_t<T, N>>
  {
    constexpr auto  c   = categorize<wide<T, N>>();
    auto const      src = alternative(mask, v, as(v));

    if      constexpr( C::is_complete )                 return src;
    else if constexpr( match(c, category::unsigned_) )  return if_else(mask, v, src);
    else                                                return svabs_m(src,expand_mask(mask, as(v)),v);
  }

  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  abs_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> const& v) noexcept requires sve_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if      constexpr(O::contains(saturated2))          return abs_(EVE_TARGETS(cpu_), opts, v);
    else if constexpr( match(c, category::unsigned_) )  return v;
    else                                                return svabs_z(sve_true<T>(),v);
  }
}
