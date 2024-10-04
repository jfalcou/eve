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
                                   C          const& mask,
                                   O          const& opts,
                                   wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto const      src = alternative(mask, w, as(w));
    if constexpr( C::is_complete )
    {
      return src;
    }
    else if constexpr(O::contains(lower) || O::contains(upper))
    {
      return sqrt.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    }
    else
    {
      auto m   = expand_mask(mask, as(w));
      return svsqrt_m(src, m, w);
    }
  }

  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_REQUIRES(sve_),
                                   O          const& opts,
                                   wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(lower) || O::contains(upper))
    {
      return sqrt.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    }
    else
      return svsqrt_z(sve_true<T>(),w);
  }

}
