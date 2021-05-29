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
  template<unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> average_(EVE_SUPPORTS(sse2_), wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr ( sizeof(T) == 2 )
    {
           if constexpr (                        std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_avg_epu16(a, b);
      else if constexpr ( current_api >= avx2 && std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_avg_epu16(a, b);
      else if constexpr (                        std::same_as<abi_t<T, N>, x86_128_> ) return _mm_avg_epu16   (a, b);
      else                                                                             return average_        (EVE_RETARGET(cpu_), a, b);
    }
    if constexpr ( sizeof(T) == 1 )
    {
           if constexpr (                        std::same_as<abi_t<T, N>, x86_512_> ) return _mm512_avg_epu8 (a, b);
      else if constexpr ( current_api >= avx2 && std::same_as<abi_t<T, N>, x86_256_> ) return _mm256_avg_epu8 (a, b);
      else if constexpr (                        std::same_as<abi_t<T, N>, x86_128_> ) return _mm_avg_epu8    (a, b);
      else                                                                             return average_        (EVE_RETARGET(cpu_), a, b);
    }
    else return average_(EVE_RETARGET(cpu_), a, b);
  }
}
