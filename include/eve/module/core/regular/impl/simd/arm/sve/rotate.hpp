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
#include <eve/detail/intrinsic_wrappers/arm/sve/sve_true.hpp>

namespace eve::_
{
  template<typename T, width_type N, std::ptrdiff_t M>
   wide<T, N> rotate_(EVE_SUPPORTS(sve_), wide<T, N> x, index_t<M>)
    requires (sve_abi<abi_t<T, N>> && (M <= N))
  {
    if constexpr (N == fundamental_width_v<T>)
    {
      return svext(x, x, M);
    }
    else
    {
      wide<make_integer_t<sizeof(T), unsigned>, fundamental_width_v<T>> indices{
        [](auto i) { return (i + M) % N; }
      };
      return svtbl(x, indices);
    }
  }
}
