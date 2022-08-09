//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/shr.hpp>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{

template<unsigned_scalar_value T, typename N>
EVE_FORCEINLINE auto
popcount_(EVE_SUPPORTS(sse2_), wide<T, N> x) noexcept requires std::same_as<abi_t<T, N>, x86_128_>
{
  auto putcounts = [](auto xx)
  {
    using N8   = fixed<N::value * sizeof(T)>;
    using i8_t = wide<std::int8_t, N8>;
    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);
    xx -= bit_shr(xx, 1) & pattern_2bit; // put count of each 2 bits into those 2 bits
    xx = (xx & pattern_4bit)
         + (bit_shr(xx, 2) & pattern_4bit);     // put count of each 4 bits into those 4 bits
    xx = (xx + bit_shr(xx, 4)) & pattern_16bit; // put count of each 8 bits into those 8 bits
    return xx;
  };

  using r_t = wide<as_integer_t<T, unsigned>, N>;
  if constexpr( sizeof(T) == 8 || sizeof(T) == 1 )
  {
    using N16   = fixed<(sizeof(T) < 8) ? 8u : sizeof(T)>;
    using i16_t = wide<uint16_t, N16>;
    auto xx     = bit_cast(x, as<i16_t>());
    if constexpr( sizeof(T) == 8 )
    {
      xx = putcounts(xx);
      return bit_cast(_mm_sad_epu8(xx, _mm_setzero_si128()), as<r_t>());
    }
    else if constexpr( sizeof(T) == 1 )
    {
      const i16_t masklow(0xff);
      return bit_cast(popcount(xx & masklow) + (popcount(bit_shr(xx, 8) & masklow) << 8),
                      as<r_t>());
    }
  }
  else if constexpr( sizeof(T) == 4 || sizeof(T) == 2 )
  {
    using N8   = fixed<N::value * sizeof(T)>;
    using i8_t = wide<std::int8_t, N8>;
    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);
    const r_t  mask(0x7f);
    x = putcounts(x);
    if constexpr( sizeof(T) >= 2 )
      x += bit_shr(x, 8); // put count of each 16 bits into their lowest 8 bits
    if constexpr( sizeof(T) >= 4 )
      x += bit_shr(x, 16); // put count of each 32 bits into their lowest 8 bits
    return bit_cast(x & mask, as<r_t>());
  }
}

/////////////////////////////////////////////////////////////////////////////
// 256 bits
template<unsigned_scalar_value T, typename N>
EVE_FORCEINLINE auto
popcount_(EVE_SUPPORTS(avx_), wide<T, N> x) noexcept requires std::same_as<abi_t<T, N>, x86_256_>
{
  using r_t = wide<as_integer_t<T, unsigned>, N>;
  if constexpr( current_api >= avx2 )
  {
    auto putcounts = [](auto xx)
    {
      using N8   = fixed<N::value * sizeof(T)>;
      using i8_t = wide<std::int8_t, N8>;
      const i8_t pattern_2bit(0x55);
      const i8_t pattern_4bit(0x33);
      const i8_t pattern_16bit(0x0f);
      xx -= bit_shr(xx, 1) & pattern_2bit; // put count of each 2 bits into those 2 bits
      xx = (xx & pattern_4bit)
           + (bit_shr(xx, 2) & pattern_4bit);     // put count of each 4 bits into those 4 bits
      xx = (xx + bit_shr(xx, 4)) & pattern_16bit; // put count of each 8 bits into those 8 bits
      return xx;
    };

    if constexpr( sizeof(T) == 8 || sizeof(T) == 1 )
    {
      using N16   = fixed<(sizeof(T) < 8) ? 16 : sizeof(T) * 2>;
      using i16_t = wide<uint16_t, N16>;
      auto xx     = bit_cast(x, as<i16_t>());
      if constexpr( sizeof(T) == 8 )
      {
        xx = putcounts(xx);
        return bit_cast(_mm256_sad_epu8(xx, _mm256_setzero_si256()), as<r_t>());
      }
      else if constexpr( sizeof(T) == 1 )
      {
        const i16_t masklow(0xff);
        return bit_cast(popcount(xx & masklow) + (popcount(bit_shr(xx, 8) & masklow) << 8),
                        as<r_t>());
      }
    }
    else if constexpr( sizeof(T) == 4 || sizeof(T) == 2 )
    {
      x = putcounts(x);
      if constexpr( sizeof(T) >= 2 )
        x += bit_shr(x, 8); // put count of each 16 bits into their lowest 8 bits
      if constexpr( sizeof(T) >= 4 )
        x += bit_shr(x, 16); // put count of each 32 bits into their lowest 8 bits
      if constexpr( sizeof(T) >= 8 )
        x += bit_shr(x, 32); // put count of each 64 bits into their lowest 8 bits
      const r_t mask(0x7f);
      return bit_cast(x & mask, as<r_t>());
    }
  }
  else
  {
    if constexpr( sizeof(T) >= 8 ) return popcount_(EVE_RETARGET(cpu_), x);
    else
    {
      auto [lo, hi] = x.slice();
      return r_t(popcount(lo), popcount(hi));
    }
  }
}
}
