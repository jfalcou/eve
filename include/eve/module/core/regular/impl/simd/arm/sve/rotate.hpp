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
  template<simd_value T, std::ptrdiff_t M>
  EVE_FORCEINLINE T rotate_(EVE_SUPPORTS(sve_), T x, index_t<M>)
    requires (M <= T::size())
  {
    return svext(x, x, M);
  }
}
