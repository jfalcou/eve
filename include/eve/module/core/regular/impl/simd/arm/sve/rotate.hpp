//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<typename T, typename N, std::ptrdiff_t M>
  EVE_FORCEINLINE wide<T, N> rotate_(EVE_SUPPORTS(sve_), wide<T, N> x, index_t<M>)
    requires (M <= N::value)
  {
    if constexpr (N::value == fundamental_cardinal_v<T>)
    {
      return svext(x, x, M);
    }
    else
    {
      wide<make_integer_t<sizeof(T), unsigned>, fundamental_cardinal_t<T>> indices{
        [](auto i, auto) { return (i + M) % N::value; }
      };
      return svtbl(x, indices);
    }
  }
}
