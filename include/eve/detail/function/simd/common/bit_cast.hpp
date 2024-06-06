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
  template<callable_options O, typename T, typename Target>
  EVE_FORCEINLINE constexpr auto bit_cast_(EVE_REQUIRES(cpu_), O const&, T const &a, as<Target> const &) noexcept
  {
    if constexpr(std::is_same_v<T, Target>) return a;
    else                                    return std::bit_cast<Target>(a);
  }
}

