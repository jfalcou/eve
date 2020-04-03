//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BIT_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BIT_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>  bit_and_(EVE_SUPPORTS(vmx_)
                                            , wide<T, N, ppc_> const &v0
                                            , wide<T, N, ppc_> const &v1) noexcept
  {
    return vec_and(v0.storage(), v1.storage());
  }
}

#endif
