//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include "eve/detail/overload.hpp"

#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                rem_(EVE_SUPPORTS(neon128_),
                     wide<T, N>        v0,
                     wide<T, N> const                &v1) noexcept requires arm_abi<abi_t<T, N>>

{
  if constexpr( current_api == neon ) return map(rem, v0, v1);
  else return rem_(EVE_RETARGET(cpu_), v0, v1);
}
}
