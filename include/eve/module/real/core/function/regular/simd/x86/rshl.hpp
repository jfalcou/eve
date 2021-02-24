//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE auto  rshl_(EVE_SUPPORTS(avx_),
                              wide<T, N, x86_128_> const &a0,
                              wide<I, N, x86_128_> const &a1)
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

