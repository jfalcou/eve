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

    const i8_t pattern_2bit(0x55);
    const i8_t pattern_4bit(0x33);
    const i8_t pattern_16bit(0x0f);
    auto xx = bit_cast(in, as<i8_t>{}); // put

    xx -= bit_shr(xx, 1) & pattern_2bit; // put
    xx  = (xx & pattern_4bit) + (bit_shr(xx, 2) & pattern_4bit);
    xx  = (xx + bit_shr(xx, 4)) & pattern_16bit; // put count of each 8 bits into those 8 bits

    return bit_cast(xx,as{in});
  };

  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> popcount_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> x) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr (sizeof(T) == 8)
    {
      using r_t = wide<T, N>;
      using u16_t = typename wide<T,N>::template rebind<std::uint16_t, fixed<8>>;

      auto xx = bit_cast(x, as<u16_t>{});

      return bit_cast(_mm_sad_epu8(putcounts<16>(xx), _mm_setzero_si128()), as<r_t>{});
    }
    else
    {
      return popcount.behavior(as<wide<T, N>>{}, cpu_{}, opts, x); 
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // 256 bits
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> popcount_(EVE_REQUIRES(avx_), O const& o, wide<T, N> x) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    using r_t = wide<T, N>;

    if constexpr (sizeof(T) == 8)
    {
      if constexpr (current_api >= avx2)
      {
        using u16_t = typename wide<T,N>::template rebind<std::uint16_t, fixed<16>>;
        auto xx = bit_cast(x, as<u16_t>{});

        return bit_cast(_mm256_sad_epu8(putcounts<32>(xx), _mm256_setzero_si256()), as<r_t>{});
      }
      else
      {
        auto [lo, hi] = x.slice();
        return r_t{popcount(lo), popcount(hi)};
      }
    }
    else
    {
      return popcount.behavior(as<wide<T, N>>{}, cpu_{}, o, x);
    }
  }
}
