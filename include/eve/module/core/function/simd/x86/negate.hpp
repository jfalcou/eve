//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_NEGATE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_NEGATE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  negate_(EVE_SUPPORTS(ssse3_)
                         , wide<T, N, sse_> const &a0, wide<T, N, sse_> const &a1) noexcept
  {
    if(std::is_integral_v<T> && std::is_signed_v<T>)
    {
      if (sizeof(T) == 8) return  map(negate, a0, a1);
      if (sizeof(T) == 4) return  _mm_sign_epi32(a0, a1);
      if (sizeof(T) == 2) return  _mm_sign_epi16(a0, a1);
      if (sizeof(T) == 1) return  _mm_sign_epi8(a0, a1);      
    }
    else
    {
      return negate_(EVE_RETARGET(cpu_), a0, a1);
    }
  }
}

#endif
