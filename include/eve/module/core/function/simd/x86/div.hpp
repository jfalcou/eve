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
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  div_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> v0, wide<T, N, sse_> const &v1) noexcept
  {
    return v0 /= v1;
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  div_(EVE_SUPPORTS(avx_), wide<T, N, avx_> v0, wide<T, N, avx_> const &v1) noexcept
  {
    return v0 /= v1;
  }
}

