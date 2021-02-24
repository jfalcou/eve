//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> average_(EVE_SUPPORTS(sse2_)
                                           , wide<T, N, x86_128_> const &a
                                           , wide<T, N, x86_128_> const &b) noexcept
  {
         if constexpr(sizeof(T) == 1) return _mm_avg_epu8(a, b);
    else if constexpr(sizeof(T) == 2) return _mm_avg_epu16(a, b);
    else                              return (a & b) + ((a ^ b) >> 1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> average_(EVE_SUPPORTS(avx_)
                                           , wide<T, N, x86_256_> const &a
                                           , wide<T, N, x86_256_> const &b) noexcept
  {
    if constexpr(current_api >= avx2)
    {
             if constexpr(sizeof(T) == 1) return _mm256_avg_epu8(a, b);
        else if constexpr(sizeof(T) == 2) return _mm256_avg_epu16(a, b);
        else                              return (a & b) + ((a ^ b) >> 1);
    }
    else                                   return average_(EVE_RETARGET(cpu_), a, b);

  }
}
