//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ANY_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ANY_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/extract.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
     
      auto [ sl, sh] = v.slice(); 
      return any(sl) || any(sh);
    }
    else 
    {
      for(int i=0; i < N::value ; ++i)
      {
        if (extract(v, i)) return true; 
      }
      return false; 
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    return any(is_nez(v)); 
  }
}

#endif
