//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/operators.hpp>

namespace eve::detail
{
  //================================================================================================
  // N parameters
  //================================================================================================
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_or_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    auto that = bit_or(r_t(a), r_t(b));
    ((that = bit_or(that, r_t(args))), ...);
    return that;
  }
}

