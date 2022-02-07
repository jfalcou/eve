//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/pedantic.hpp>
#include <eve/module/core/regular/impl/simd/x86/rsqrt.hpp>


namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Pedantic 128 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_)
                             , pedantic_type const &
                             , wide<T, N>    const &a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    return rsqrt_x86_pedantic(a0);
  }
}
