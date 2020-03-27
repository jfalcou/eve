//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>

namespace eve::detail
{
  template<_scalar_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> abs_(EVE_SUPPORTS(vmx_)
                                       , wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(unsigned_scalar_value<T>)
    {
      return v0;
    }
    else if constexpr(signed_integral_scalar_value<T> && (sizeof(T) > 4))
    {
      return map(eve::abs, v0);
    }
    else
    {
      return vec_abs(v0.storage());
    }
  }
}

#endif
