//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{

  template<callable_options O, floating_scalar_value T, typename N, conditional_expr C>
  EVE_FORCEINLINE logical<wide<T, N>> is_unordered_(EVE_REQUIRES(sve_), C const& mask, O const& opts,
                                  wide<T, N> v, wide<T, N> w) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    auto const alt = alternative(mask, v, as(v));

    // ignore all just return alternative
    if constexpr( C::is_complete ) return alt;
    //  If not, we can mask if there is no alterative value
    if  constexpr (!C::has_alternative)
    {
      auto m = expand_mask(mask, as(v));
      return svcmpuo(m,v,w);
    }
    // If not, we delegate to the automasking
    else
    {
      return is_unordered.behavior(cpu_{}, opts && mask, v, w);
    }
  }

  template<callable_options O, floating_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_unordered_(EVE_REQUIRES(sve_), O const&,
                                 wide<T, N> v, wide<T, N> w) noexcept
  requires (sve_abi<abi_t<T, N>>)
  {
    return svcmpuo(sve_true<T>(), v, w);
  }
}
