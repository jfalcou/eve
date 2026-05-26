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

namespace eve::_
{
  template<typename T, size_type N, std::ptrdiff_t M>
  EVE_FORCEINLINE wide<T, N> rotate_(EVE_SUPPORTS(sve_), wide<T, N> x, index_t<M>)
    requires (sve_abi<abi_t<T, N>> && (M <= N))
  {
    if constexpr (N == fundamental_cardinal_v<T>)
    {
      return svext(x, x, M);
    }
    else
    {
      wide<make_integer_t<sizeof(T), unsigned>, fundamental_cardinal_v<T>> indices{
        [](auto i) { return (i + M) % N; }
      };
      return svtbl(x, indices);
    }
  }
}
