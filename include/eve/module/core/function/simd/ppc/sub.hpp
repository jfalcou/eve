//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SUB_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SUB_HPP_INCLUDED

#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  sub_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> v0, wide<T, N, ppc_> const &v1) noexcept
  {
    return v0 -= v1;
  }
}

#endif
