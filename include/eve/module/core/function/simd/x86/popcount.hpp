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
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_shl.hpp>
#include <eve/function/gather.hpp>
#include <bit>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{
  template<integral_scalar_value T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx_)
                                , wide<T, N, ABI>  x) noexcept
  requires ((std::is_same_v<ABI, avx_> || std::is_same_v<ABI, sse_>) && (sizeof(T) <  8) && (sizeof(T) >  1))
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    using N8 = fixed<N::value*sizeof(T)>;
    using i8_t = wide<std::int8_t, N8>;
    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);
    const r_t mask(0x7f);
    x -= bit_shr(x, 1) & pattern_2bit;                        //put count of each 2 bits into those 2 bits
    x = (x & pattern_4bit) + (bit_shr(x, 2) & pattern_4bit);  //put count of each 4 bits into those 4 bits
    x = (x + bit_shr(x, 4)) & pattern_16bit;                  //put count of each 8 bits into those 8 bits
    if constexpr(sizeof(T) >= 2) x += bit_shr(x,  8);         //put count of each 16 bits into their lowest 8 bits
    if constexpr(sizeof(T) >= 4) x += bit_shr(x, 16);         //put count of each 32 bits into their lowest 8 bits
    if constexpr(sizeof(T) == 8) x += bit_shr(x, 32);         //put count of each 64 bits into their lowest 8 bit
    return bit_cast(x & mask, as<r_t>());
  }

  template<integral_scalar_value T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx_)
                                , wide<T, N, ABI>  x) noexcept
  requires ((std::is_same_v<ABI, avx_> || std::is_same_v<ABI, sse_> ) && (sizeof(T) == 1))
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    using N16 = fixed<N::value/2>;
    using i16_t = wide<std::uint16_t, N16>;
    auto xx =  bit_cast(x, as<i16_t>());
    const i16_t masklow(0xff);
    return bit_cast(popcount(xx&masklow)+ bit_shl(popcount(bit_shr(xx, 8)&masklow), 8), as<r_t>());
  }

  template<integral_scalar_value T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx_)
                                , wide<T, N, ABI>  xx) noexcept
  requires ((std::is_same_v<ABI, avx_> || std::is_same_v<ABI, sse_>) && (sizeof(T) == 8))
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    using N16 = fixed<N::value*4>;
    using i16_t = wide<std::uint16_t, N16>;
    auto x =  bit_cast(xx, as<i16_t>());
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    using N8 = fixed<N::value*sizeof(T)>;
    using i8_t = wide<std::uint8_t, N8>;
    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);

    x -=  bit_shr(x, 1) & pattern_2bit;                        //put count of each 2 bits into those 2 bits
    x = (x & pattern_4bit) + ( bit_shr(x, 2) & pattern_4bit);  //put count of each 4 bits into those 4 bits
    x = (x +  bit_shr(x, 4)) & pattern_16bit;                  //put count of each 8 bits into those 8 bits
    if constexpr(std::is_same_v<ABI, avx_>)
      return  bit_cast(_mm256_sad_epu8(x.storage(), _mm256_setzero_si256()), as<r_t>());
    else if constexpr(std::is_same_v<ABI, sse_>)
      return  bit_cast(_mm_sad_epu8(x.storage(), _mm_setzero_si128()), as<r_t>());
  }

}
