//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> trunc_(EVE_SUPPORTS(vmx_)
                                         , wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(integral_value<T>)      return vec_trunc(v0.storage());
    else if constexpr(floating_value<T>) return v0;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> trunc_(EVE_SUPPORTS(vmx_)
                                         , raw_type const & 
                                         , wide<T, N, ppc_> const &v0) noexcept
  {
    return trunc(v0); 
  }
 
}

#endif
