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
  template<floating_scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N> ilogb_(EVE_REQUIRES(sve_),
                                    C          const& mask,
                                    O          const& opts,
                                    wide<T, N> const& v) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    constexpr auto  c   = categorize<wide<T, N>>();
    auto const      src = alternative(mask, v, as(v));

    if      constexpr( C::is_complete )                 return src;
    else    return svlogb(src,expand_mask(mask, as(v)),v);
  }

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> ilogb_(EVE_REQUIRES(sve_),
                                  O          const& opts,
                                  wide<T, N> const& v) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    return svlogb(sve_true<T>(),v);
  }
}
