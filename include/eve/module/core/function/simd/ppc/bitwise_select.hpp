//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> bitwise_select_(EVE_SUPPORTS(vmx_),
                                                   wide<U, N, ppc_> const &m,
                                                   wide<T, N, ppc_> const &v0,
                                                   wide<T, N, ppc_> const &v1) noexcept
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;

    return vec_sel(v1.storage(), v0.storage(), bitwise_cast(m,as_<i_t>()).storage());
  }
}

#endif
