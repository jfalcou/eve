//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> fma_(EVE_SUPPORTS(vmx_),
                                        wide<T, N, ppc_> const &v0,
                                        wide<T, N, ppc_> const &v1,
                                        wide<T, N, ppc_> const &v2) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    { return vec_madd(v0.storage(), v1.storage(), v2.storage()); }
    else
    {
      return v0.storage() * v1.storage() + v2.storage();
    }
  }

  template<typename D, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> fma_(EVE_SUPPORTS(vmx_),
                                        D const &, 
                                        wide<T, N, ppc_> const &v0,
                                        wide<T, N, ppc_> const &v1,
                                        wide<T, N, ppc_> const &v2) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    { return vec_madd(v0.storage(), v1.storage(), v2.storage()); }
    else
    {
      return v0.storage() * v1.storage() + v2.storage();
    }
  }  
}

#endif
