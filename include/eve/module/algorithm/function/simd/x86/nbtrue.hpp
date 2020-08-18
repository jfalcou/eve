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
#include <eve/detail/concepts.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // X86 implementation
  //================================================================================================
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto nbtrue_(EVE_SUPPORTS(sse2_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return v.bitmap().count();
  }
}
