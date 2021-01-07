//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //================================================================================================
  // operator~ implementation
  //================================================================================================
  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    return vec_nor(v0storage(), v.storage());
  }
}
