//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T,N,ABI>> to_logical( wide<T,N,ABI> const& v ) noexcept
  {
    return as_logical_t<wide<T,N,ABI>>(vec_cmpne(v.storage(), wide<T,N,ABI>{0}.storage()));
  }
}
