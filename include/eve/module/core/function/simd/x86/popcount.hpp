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

#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_shl.hpp>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{

  template<integral_scalar_value T,  typename N>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(sse2_), wide<T, N, sse_>  x) noexcept
  {
    auto putcounts = [](auto xx){
      using N8 = fixed<N::value*sizeof(T)>;
      using i8_t = wide<std::int8_t, N8>;
      const i8_t pattern_2bit(0x55);
      const i8_t pattern_4bit(0x33);
      const i8_t pattern_16bit(0x0f);
      xx -=  bit_shr(xx, 1) & pattern_2bit;                         //put count of each 2 bits into those 2 bits
      xx = (xx & pattern_4bit) + ( bit_shr(xx, 2) & pattern_4bit);  //put count of each 4 bits into those 4 bits
      xx = (xx +  bit_shr(xx, 4)) & pattern_16bit;                  //put count of each 8 bits into those 8 bits
      return xx;
    };

     using r_t = wide<as_integer_t<T, unsigned>, N>;
    if constexpr(sizeof(T) == 8 || sizeof(T) == 1)
    {
      using N16 = fixed< (sizeof(T) < 8) ? 8u : sizeof(T)>;
      using i16_t = wide < uint16_t, N16>; //typename wide<T,N,avx_>::template rebind<uint16_t,N16>;
      auto xx =  bit_cast(x, as<i16_t>());
      if constexpr(sizeof(T) == 8)
      {
        xx = putcounts(xx);
       return  bit_cast(_mm_sad_epu8(xx.storage(), _mm_setzero_si128()), as<r_t>());
      }
      else if constexpr(sizeof(T) == 1)
      {
        const i16_t masklow(0xff);
        return bit_cast(popcount(xx&masklow)+ bit_shl(popcount(bit_shr(xx, 8)&masklow), 8), as<r_t>());
      }
    }
    else if constexpr(sizeof(T) == 4 || sizeof(T) == 2)
    {
      using N8 = fixed<N::value*sizeof(T)>;
      using i8_t = wide<std::int8_t, N8>;
      const i8_t pattern_2bit(0x55);
      const i8_t pattern_4bit(0x33);
      const i8_t pattern_16bit(0x0f);
      const r_t mask(0x7f);
      x = putcounts(x);
      if constexpr(sizeof(T) >= 2) x += bit_shr(x,  8);         //put count of each 16 bits into their lowest 8 bits
      if constexpr(sizeof(T) >= 4) x += bit_shr(x, 16);         //put count of each 32 bits into their lowest 8 bits
      return bit_cast(x & mask, as<r_t>());
    }
  }

 template<integral_scalar_value T,  typename N>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx_), wide<T, N, avx_>  x) noexcept
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    auto putcounts = [](auto xx){
      using N8 = fixed<N::value*sizeof(T)>;
      using i8_t = wide<std::int8_t, N8>;
      const i8_t pattern_2bit(0x55);
      const i8_t pattern_4bit(0x33);
      const i8_t pattern_16bit(0x0f);
      xx -=  bit_shr(xx, 1) & pattern_2bit;                         //put count of each 2 bits into those 2 bits
      xx = (xx & pattern_4bit) + ( bit_shr(xx, 2) & pattern_4bit);  //put count of each 4 bits into those 4 bits
      xx = (xx +  bit_shr(xx, 4)) & pattern_16bit;                  //put count of each 8 bits into those 8 bits
      return xx;
    };

    if constexpr(sizeof(T) == 8 || sizeof(T) == 1)
    {
      using N16 = fixed<(sizeof(T) < 8) ? 16 : sizeof(T)*2>;
      using i16_t = wide<uint16_t, N16>;
      auto xx =  bit_cast(x, as<i16_t>());
      if constexpr(sizeof(T) == 8)
      {
        xx =  putcounts(xx);
        return  bit_cast(_mm256_sad_epu8(xx.storage(), _mm256_setzero_si256()), as<r_t>());
      }
      else if constexpr(sizeof(T) == 1)
      {
        const i16_t masklow(0xff);
        return bit_cast(popcount(xx&masklow)+ bit_shl(popcount(bit_shr(xx, 8)&masklow), 8), as<r_t>());
      }
    }
    else if constexpr(sizeof(T) == 4 || sizeof(T) == 2)
    {
      x =  putcounts(x);
      if constexpr(sizeof(T) >= 2) x += bit_shr(x,  8);         //put count of each 16 bits into their lowest 8 bits
      if constexpr(sizeof(T) >= 4) x += bit_shr(x, 16);         //put count of each 32 bits into their lowest 8 bits
      const r_t mask(0x7f);
      return bit_cast(x & mask, as<r_t>());
    }
  }
}
