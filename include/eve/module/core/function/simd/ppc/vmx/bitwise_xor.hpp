//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  bitwise_xor_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, wide<T, N, ppc_> const &v1) noexcept
  {
    return vec_xor(v0.storage(), v1.storage());
  }
}

#endif
