//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_NEAREST_HPP_INCLUDED

#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> nearest_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<T, float>) { return vec_round(v0.storage()); }
    else if constexpr(std::is_same_v<T, double>)
    {
      // TODO(joel) : Test on proper VSX HW
      return map(eve::nearest, v0);
    }
  }
}

#endif
