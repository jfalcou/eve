//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>

#include <cmath>

namespace eve::detail
{

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_REQUIRES(cpu_),
                                    O const&,
                                    T const& a0) noexcept
  {
    if constexpr( scalar_value<T> )
      return std::sqrt(a0);
    else
      return map(eve::sqrt, a0);
  }
}
