//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  template<typename T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T,N>> to_logical( wide<T,N> const& v ) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return as_logical_t<wide<T,N>>(vec_cmpne(v.storage(), wide<T,N>{0}.storage()));
  }
}
