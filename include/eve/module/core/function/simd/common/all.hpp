//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/extract.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
     
      auto [ sl, sh] = v.slice(); 
      return all(sl) && all(sh);
    }
    else 
    {
      for(int i=0; i < N::value ; ++i)
      {
        if (!extract(v, i)) return false; 
      }
      return true; 
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    return all(is_nez(v)); 
  }
}

#endif
