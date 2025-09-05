//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/category.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> to_logical( wide<T,N> const& v ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return v != 0;
  }
}
