//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_>
                  mul_(EVE_SUPPORTS(sse2_), wide<T, N, x86_128_> v0, wide<T, N, x86_128_> const &v1) noexcept
  {
    return v0 *= v1;
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_>
                  mul_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> v0, wide<T, N, x86_256_> const &v1) noexcept
  {
    return v0 *= v1;
  }


}
