//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_BITWISE_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T0, typename N0, typename T1, typename N1>
  EVE_FORCEINLINE wide<T0,N0,ppc_> bitwise_and_ ( EVE_SUPPORTS(vmx_)
                                                , wide<T0,N0,ppc_> const& v0
                                                , wide<T1,N1,ppc_> const& v1
                                                ) noexcept
  {
    return vec_and(v0.storage(), bitwise_cast<wide<T0,N0,ppc_>>(v1).storage());
  }
}

#endif
