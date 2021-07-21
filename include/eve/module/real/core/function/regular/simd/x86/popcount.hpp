//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/if_else.hpp>

#if defined(SPY_COMPILER_IS_MSVC)
#  include <intrin.h>
#endif

namespace eve::detail
{

  template<unsigned_scalar_value T,  typename N>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(sse2_), wide<T, N>  x) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
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
      using i16_t = wide < uint16_t, N16>;
      auto xx =  bit_cast(x, as<i16_t>());
      if constexpr(sizeof(T) == 8)
      {
        xx = putcounts(xx);
       return  bit_cast(_mm_sad_epu8(xx, _mm_setzero_si128()), as<r_t>());
      }
      else if constexpr(sizeof(T) == 1)
      {
        const i16_t masklow(0xff);
        return bit_cast(popcount(xx&masklow)+ (popcount(bit_shr(xx, 8)&masklow) << 8), as<r_t>());
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

  /////////////////////////////////////////////////////////////////////////////
  // 256 bits
  template<unsigned_scalar_value T,  typename N>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx_), wide<T, N>  x) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    if constexpr( current_api >=  avx2)
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

      if constexpr(sizeof(T) == 8 || sizeof(T) == 1)
      {
        using N16 = fixed<(sizeof(T) < 8) ? 16 : sizeof(T)*2>;
        using i16_t = wide<uint16_t, N16>;
        auto xx =  bit_cast(x, as<i16_t>());
        if constexpr(sizeof(T) == 8)
        {
          xx =  putcounts(xx);
          return  bit_cast(_mm256_sad_epu8(xx, _mm256_setzero_si256()), as<r_t>());
        }
        else if constexpr(sizeof(T) == 1)
        {
          const i16_t masklow(0xff);
          return bit_cast(popcount(xx&masklow)+ (popcount(bit_shr(xx, 8)&masklow) <<  8), as<r_t>());
        }
      }
      else if constexpr( sizeof(T) == 4 || sizeof(T) == 2)
      {
        x =  putcounts(x);
        if constexpr(sizeof(T) >= 2) x += bit_shr(x,  8);         //put count of each 16 bits into their lowest 8 bits
        if constexpr(sizeof(T) >= 4) x += bit_shr(x, 16);         //put count of each 32 bits into their lowest 8 bits
        if constexpr(sizeof(T) >= 8) x += bit_shr(x, 32);         //put count of each 64 bits into their lowest 8 bits
        const r_t mask(0x7f);
        return bit_cast(x & mask, as<r_t>());
      }
    }
    else
    {
      if constexpr(sizeof(T) >= 8)
        return popcount_(EVE_RETARGET(cpu_), x);
      else
      {
        auto [lo, hi] = x.slice();
        return r_t(popcount(lo), popcount(hi));
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // avx512
  template<unsigned_scalar_value T,  typename N>
  EVE_FORCEINLINE auto popcount_(EVE_SUPPORTS(avx512_), wide<T, N>  v) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    auto constexpr bitalg = spy::supports::avx512::bitalg_;
    auto constexpr ppctdq = spy::supports::avx512::popcntdq_;
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    constexpr auto c = categorize<wide<T, N>>();
            if constexpr(bitalg && c == category::uint16x32 ) return r_t(_mm512_popcnt_epi16(v));//bitalg
      else  if constexpr(bitalg && c == category::uint16x16 ) return r_t(_mm256_popcnt_epi16(v));//bitalg
      else  if constexpr(bitalg && c == category::uint16x8  ) return r_t(_mm_popcnt_epi16   (v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x64  ) return r_t(_mm512_popcnt_epi8 (v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x32  ) return r_t(_mm256_popcnt_epi8 (v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x16  ) return r_t(_mm_popcnt_epi8    (v));//bitalg
      else  if constexpr(bitalg && c == category::int16x32  ) return r_t(_mm512_popcnt_epi16(v)); //bitalg
      else  if constexpr(bitalg && c == category::int16x16  ) return r_t(_mm256_popcnt_epi16(v)); //bitalg
      else  if constexpr(bitalg && c == category::int16x8   ) return r_t(_mm_popcnt_epi16   (v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x64   ) return r_t(_mm512_popcnt_epi8 (v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x32   ) return r_t(_mm256_popcnt_epi8 (v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x16   ) return r_t(_mm_popcnt_epi8    (v)); //bitalg
      else  if constexpr(ppctdq && c == category::int64x8   ) return r_t(_mm512_popcnt_epi64(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int64x4   ) return r_t(_mm256_popcnt_epi64(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int64x2   ) return r_t(_mm_popcnt_epi64   (v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x16  ) return r_t(_mm512_popcnt_epi32(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x8   ) return r_t(_mm256_popcnt_epi32(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x4   ) return r_t(_mm_popcnt_epi32   (v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x8  ) return r_t(_mm512_popcnt_epi64(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x4  ) return r_t(_mm256_popcnt_epi64(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x2  ) return r_t(_mm_popcnt_epi64   (v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x16 ) return r_t(_mm512_popcnt_epi32(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x8  ) return r_t(_mm256_popcnt_epi32(v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x4  ) return r_t(_mm_popcnt_epi32   (v));//avx512vpopcntdq
      return popcount_(EVE_RETARGET(avx_), v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto popcount_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    using r_t = wide<as_integer_t<T, unsigned>, N>;
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return popcount_(EVE_RETARGET(cpu_),cx,v);
    }
    else
    {
      auto constexpr bitalg = spy::supports::avx512::bitalg_;
      auto constexpr ppctdq = spy::supports::avx512::popcntdq_;
      auto src  = alternative(cx,r_t(v),as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

            if constexpr(bitalg && c == category::int16x32  ) return r_t(_mm512_mask_popcnt_epi16(src,m,v)); //bitalg
      else  if constexpr(bitalg && c == category::int16x16  ) return r_t(_mm256_mask_popcnt_epi16(src,m,v)); //bitalg
      else  if constexpr(bitalg && c == category::int16x8   ) return r_t(_mm_mask_popcnt_epi16   (src,m,v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x64   ) return r_t(_mm512_mask_popcnt_epi8 (src,m,v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x32   ) return r_t(_mm256_mask_popcnt_epi8 (src,m,v)); //bitalg
      else  if constexpr(bitalg && c == category::int8x16   ) return r_t(_mm_mask_popcnt_epi8    (src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint16x32 ) return r_t(_mm512_mask_popcnt_epi16(src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint16x16 ) return r_t(_mm256_mask_popcnt_epi16(src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint16x8  ) return r_t(_mm_mask_popcnt_epi16   (src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x64  ) return r_t(_mm512_mask_popcnt_epi8 (src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x32  ) return r_t(_mm256_mask_popcnt_epi8 (src,m,v));//bitalg
      else  if constexpr(bitalg && c == category::uint8x16  ) return r_t(_mm_mask_popcnt_epi8    (src,m,v));//bitalg
      else  if constexpr(ppctdq && c == category::int64x8   ) return r_t(_mm512_mask_popcnt_epi64(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int64x4   ) return r_t(_mm256_mask_popcnt_epi64(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int64x2   ) return r_t(_mm_mask_popcnt_epi64   (src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x16  ) return r_t(_mm512_mask_popcnt_epi32(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x8   ) return r_t(_mm256_mask_popcnt_epi32(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::int32x4   ) return r_t(_mm_mask_popcnt_epi32   (src,m,v)); //avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x8  ) return r_t(_mm512_mask_popcnt_epi64(src,m,v)); //avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x4  ) return r_t(_mm256_mask_popcnt_epi64(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint64x2  ) return r_t(_mm_mask_popcnt_epi64   (src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x16 ) return r_t(_mm512_mask_popcnt_epi32(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x8  ) return r_t(_mm256_mask_popcnt_epi32(src,m,v));//avx512vpopcntdq
      else  if constexpr(ppctdq && c == category::uint32x4  ) return r_t(_mm_mask_popcnt_epi32   (src,m,v));//avx512vpopcntdq
      else    return  popcount_(EVE_RETARGET(cpu_),cx,v);
    }
  }
}
