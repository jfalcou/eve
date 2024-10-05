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
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> dist_(EVE_REQUIRES(sve_), O const& opts,
                                   wide<T, N> v, wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    if constexpr((O::contains(saturated) && std::integral<T>) || O::contains(lower) || O::contains(upper))
      return dist.behavior(cpu_{}, opts, v, w);
    else
      return svabd(v, w); 
  }
}
