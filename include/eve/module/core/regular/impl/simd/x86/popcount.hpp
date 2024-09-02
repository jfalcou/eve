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
  template<auto S, typename T, typename N>
  EVE_FORCEINLINE auto putcounts(wide<T, N> in)
  {
    using i8_t = typename wide<T,N>::template rebind<std::uint8_t, fixed<S>>;

    }
    else if constexpr( sizeof(T) == 4 || sizeof(T) == 2 )
    {
      using i8_t = typename wide<T,N>::template rebind<std::uint8_t>;
      const i8_t pattern_2bit(0x55);
      const i8_t pattern_4bit(0x33);
      const i8_t pattern_16bit(0x0f);
      const r_t  mask(0x7f);

      x = putcounts(x);
      if constexpr( sizeof(T) >= 2 ) x += bit_shr(x,  8); // put count of each 16 bits into their lowest 8 bits
      if constexpr( sizeof(T) >= 4 ) x += bit_shr(x, 16); // put count of each 32 bits into their lowest 8 bits
      return bit_cast(x & mask, as(mask));
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // 256 bits
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto popcount_(EVE_REQUIRES(avx_), O const& o, wide<T, N> x) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    using r_t = wide<T, N>;
    if constexpr( current_api >= avx2 )
    {
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
      if constexpr( sizeof(T) >= 8 )
        return popcount.behavior(cpu_{}, o, x);
      else
      {
        auto [lo, hi] = x.slice();
        return r_t(popcount(lo), popcount(hi));
      }
    }
  }
}
