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
  template<value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
  EVE_FORCEINLINE T
  swap_pairs_(EVE_SUPPORTS(cpu_), T x
                  , index_t<I0> const &
                  , index_t<I1> const &  ) noexcept
  {
    [[maybe_unused]] constexpr std::ptrdiff_t C = scalar_value<T> ? 1 : cardinal_v<T>;
    EVE_ASSERT((I0 >= 0) && (I1 >= 0) && (I0 < C) && (I1 < C), "some index(es) are out or range");
    if constexpr(simd_value<T>)
    {
      auto p = [](auto i,  auto){
       return (i == I0) ? I1 :(i == I1 ? I0 : i) ;
      };
      return eve::shuffle(x, eve::as_pattern(p));
    }
    else if constexpr(scalar_value<T>)
    {
      return x;
    }
  }
}
