//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE auto  rshl_(EVE_SUPPORTS(avx_),
                              wide<T, N, sse_> const &a0,
                              wide<I, N, sse_> const &a1)
  {
    if constexpr(supports_xop)
    {
      if(std::is_signed_v<I>)
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm_sha_epi8(a0, a1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_sha_epi16(a0, a1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_sha_epi32(a0, a1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_sha_epi64(a0, a1);
        }
      }
      else
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm_shl_epi8(a0, a1);
        }
        else if constexpr(sizeof(T) == 2)
        {
          return _mm_shl_epi16(a0, a1);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_shl_epi32(a0, a1);
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_shl_epi64(a0, a1);
        }
      }
    }
    else
    {
      return map(eve::rshl, a0, a1); //TODO pas génial
    }
  }
}

#endif
