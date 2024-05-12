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

namespace eve::detail
{
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T,N> mul_((EVE_SUPPORTS(sve_),
                                  C          const& mask,
                                  O          const& opts,
                                  wide<T, N> const& v,
                                  wide<T, N> const& w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, v, as(v));

    // ignore all just return alternative
    if constexpr( C::is_complete ) return alt;
    else
    {
      //  if saturated on integer, we don't have masked op so we delegate
      if        constexpr(O::contains(saturated2) && std::integral<T>) return mul.behavior(cpu_{},opts,v,w);
      //  If not, we can mask if there is no alterative value
      else  if  constexpr( !C::has_alternative )
      {
        auto m   = expand_mask(mask, as(v));
        return svmul_m(m,v,w);
      }
      // If not, we delegate to the automasking
      else
      {
        return mul.behavior(cpu_{},opts,v,w);
      }

    }
  }
}
