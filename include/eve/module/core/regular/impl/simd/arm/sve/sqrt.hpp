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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>


namespace eve::detail
{
  template<floating_scalar_value T, typename N, conditional_expr C, callable_options O>
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_REQUIRES(sve_),
                                   O const& opts,
                                   C const& cond,
                                   V const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    constexpr auto  c   = categorize<wide<T, N>>();
    auto const      src = alternative(mask, v, as(v));
    if constexpr( C::is_complete )
    {
      return src;
    }
    else
    {
      auto m   = expand_mask(cond, as(v));
      return svsqrt_m(src, m, v);
    }
  }

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto
  sqrt_(EVE_REQUIRES(sve_), wide<T, N> const& v) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    return svsqrt_z(sve_true<T>(),v);
  }

}
