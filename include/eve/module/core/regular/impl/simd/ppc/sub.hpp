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
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>


namespace eve::detail
{

template<callable_options O, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N> sub_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires ppc_abi<abi_t<T, N>>
{
  if constexpr(O::contains(lower) || O::contains(upper)) return sub.behavior(cpu_{}, opts, a, b);
  else if constexpr (O::contains(saturated) && std::integral<T>) return sub.behavior(cpu_{}, opts, a, b);
  else                                                            return vec_sub(a.storage(), b.storage());

}

}
