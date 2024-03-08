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
template<arithmetic_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> max_(EVE_REQUIRES(vmx_),
                                O          const &opts,
                                wide<T, N> const &v0,
                                wide<T, N> const &v1) noexcept requires ppc_abi<abi_t<T, N>>
{
   if constexpr(O::contains(numeric2) || O::contains(pedantic2))
      return max_(EVE_TARGETS(cpu_), opts, v0, v1);
    else
      return vec_max(v0.storage(), v1.storage());
}
}
