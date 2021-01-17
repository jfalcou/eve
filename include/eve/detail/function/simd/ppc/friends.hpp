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

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // operator~ implementation
  //================================================================================================
  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    return vec_nor(v.storage(), v.storage());
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_eq(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    return as_logical_t<wide<T,N,ABI>>(vec_cmpeq(v.storage(), w.storage()));
  }
}
