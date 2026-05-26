//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/spy.hpp>
#include <eve/traits.hpp>
#include <bit>

namespace eve::_
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto popcount_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
  {
    if constexpr( scalar_value<T> ) return T(std::popcount(x));
    else                            return map(popcount,x);
  }
}
