//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, simd_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
  EVE_FORCEINLINE constexpr T swap_pairs_(EVE_REQUIRES(cpu_), O const&, T x, index_t<I0>, index_t<I1>) noexcept
  {
    constexpr std::ptrdiff_t C = cardinal_v<T>;
    static_assert((I0 >= 0) && (I1 >= 0) && (I0 < C) && (I1 < C), "some index(es) are out or range");
    
    auto p = [](auto i,  auto){
      return (i == I0) ? I1 :(i == I1 ? I0 : i) ;
    };

    return eve::shuffle(x, eve::as_pattern(p));
  }
}
