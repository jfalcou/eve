//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Pedantic 128 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_)
                             , pedantic_type const &
                             , wide<T, N, x86_128_> const &a0) noexcept
  {
     return rsqrt_x86_pedantic(a0);
  }
}
