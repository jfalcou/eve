//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <eve/as.hpp>
#include <eve/traits.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/gather.hpp>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<integral_scalar_value T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(sse2_)
                                , wide<T, N, ABI>  x) noexcept
  requires (std::is_same_v<ABI, sse_> || std::is_same_v<ABI, avx_>)
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    using N8 = fixed<N::value*sizeof(T)>;
    using i8_t = wide<std::int8_t, N8>;
    // r_t x =  bit_cast(v, as<r_t>());
    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);
    const r_t mask(0x7f);
    x -= (x >> 1) & pattern_2bit;                        //put count of each 2 bits into those 2 bits
    x = (x & pattern_4bit) + ((x >> 2) & pattern_4bit);  //put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & pattern_16bit;                  //put count of each 8 bits into those 8 bits
    if constexpr(sizeof(T) == 8)
    {
      if constexpr(std::is_same_v<ABI, sse_>)
        return  bit_cast(_mm_sad_epu8(x, _mm_setzero_si128()), as<r_t>());
      else
        return  bit_cast(_mm256_sad_epu8(x, _mm256_setzero_si256()), as<r_t>());
    }
    if constexpr(sizeof(T) >= 2) x += x >>  8;           //put count of each 16 bits into their lowest 8 bits
    if constexpr(sizeof(T) >= 4) x += x >> 16;           //put count of each 32 bits into their lowest 8 bits
    return bit_cast(x & mask, as<r_t>());
  }

}
