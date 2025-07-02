//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <bit>

namespace eve::detail
{
  template<typename T, typename Target>
  EVE_FORCEINLINE constexpr auto bit_cast_impl(cpu_, T const &a, as<Target>) noexcept
  {
    // Fixes bad codegen on some compilers
    if constexpr(std::is_same_v<T, Target>) return a;
    else                                    return std::bit_cast<Target>(a);
  }
}

