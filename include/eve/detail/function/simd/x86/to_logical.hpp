//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T,N>> to_logical( wide<T,N> const& v ) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    return v != 0;
  }
}
