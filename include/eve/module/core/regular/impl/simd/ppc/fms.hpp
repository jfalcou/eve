//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N>
  fms_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> const& a, wide<T, N> const& b, wide<T, N> const& c) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    // REGULAR ---
    // Only floating point has a special behavior and are PEDANTIC by design
    if constexpr( std::floating_point<T> && !(O::contains(lower) || O::contains(upper)))
      return vec_madd(a.storage(), b.storage(), minus(c).storage());
    // PEDANTIC, INTEGRAL, UPPER, ETC... ---
    // We don't care about PROMOTE as we only accept similar types.
    else
      return fms.behavior(cpu_{}, opts, a, b, c);
  }
}
