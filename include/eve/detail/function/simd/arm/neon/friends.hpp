//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // operator!= implementation
  //================================================================================================
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_neq(wide<T,N> v, wide<T,N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return !(v == w);
  }
}
