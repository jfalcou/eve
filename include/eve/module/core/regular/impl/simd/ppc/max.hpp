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
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                max_(EVE_SUPPORTS(vmx_),
                     wide<T, N> const                &v0,
                     wide<T, N> const                &v1) noexcept requires ppc_abi<abi_t<T, N>>
{
  return vec_max(v0.storage(), v1.storage());
}
}
