//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_neq(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return logical<wide<T,N>>(vec_cmpne(v.storage(), w.storage()));
  }
}
