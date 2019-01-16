//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE pack<T,N,ppc_> plus_( EVE_SUPPORTS(vmx_)
                                      , pack<T,N,ppc_> const& v0
                                      , pack<T,N,ppc_> const& v1
                                      ) noexcept
  {
    return vec_add(v0.storage(),v1.storage());
  }
}

#endif
