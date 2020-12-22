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

#include <eve/concept/value.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>>
  is_greater_(EVE_SUPPORTS(sse2_), wide<T,N,ABI> const &v0, wide<T,N,ABI> const &v1) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::gt_oq);

    if constexpr( !ABI::is_wide_logical )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v0, v1, f) };
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v0, v1, f) };
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v0, v1, f) };
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v0, v1, f) };
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v0, v1, f) };
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v0, v1, f) };
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpgt_epu64_mask(v0,v1)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpgt_epu64_mask(v0,v1)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpgt_epu64_mask   (v0,v1)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpgt_epu32_mask(v0,v1)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpgt_epu32_mask(v0,v1)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpgt_epu32_mask   (v0,v1)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpgt_epu16_mask(v0,v1)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpgt_epu16_mask(v0,v1)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpgt_epu16_mask    (v0,v1)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpgt_epu8_mask (v0,v1)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpgt_epu8_mask (v0,v1)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpgt_epu8_mask    (v0,v1)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpgt_epi64_mask(v0,v1)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpgt_epi64_mask(v0,v1)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpgt_epi64_mask   (v0,v1)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpgt_epi32_mask(v0,v1)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpgt_epi32_mask(v0,v1)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpgt_epi32_mask   (v0,v1)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpgt_epi16_mask(v0,v1)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpgt_epi16_mask(v0,v1)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpgt_epi16_mask   (v0,v1)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpgt_epi8_mask (v0,v1)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpgt_epi8_mask (v0,v1)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpgt_epi8_mask    (v0,v1)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v0,v1,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v0,v1,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpgt_ps(v0,v1);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpgt_pd(v0,v1);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comgt_epu64(v0,v1);
        else  if constexpr( c == category::uint32x4 ) return _mm_comgt_epu32(v0,v1);
        else  if constexpr( c == category::uint16x8 ) return _mm_comgt_epu16(v0,v1);
        else  if constexpr( c == category::uint8x16 ) return _mm_comgt_epu8 (v0,v1);
        else  if constexpr( c == category::int64x2  ) return _mm_comgt_epi64(v0,v1);
        else  if constexpr( c == category::int32x4  ) return _mm_comgt_epi32(v0,v1);
        else  if constexpr( c == category::int16x8  ) return _mm_comgt_epi16(v0,v1);
        else  if constexpr( c == category::int8x16  ) return _mm_comgt_epi8 (v0,v1);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        constexpr auto use_sse4 = current_api >= sse4_2;

        [[maybe_unused]]  auto unsigned_cmp = [](auto v0, auto v1)
        {
          using l_t = logical<wide<T, N, ABI>>;
          auto const sm = signmask(as_<as_integer_t<wide<T, N, ABI>, signed>>());
          return bit_cast( eve::is_greater( bit_cast(v0,as(sm))-sm, bit_cast(v1,as(sm))-sm),
                           as_<l_t>{}
                         );
        };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_cmpgt_epi64(v0,v1);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return unsigned_cmp(v0,v1);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_cmpgt_epi32(v0,v1);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return unsigned_cmp(v0,v1);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_cmpgt_epi16(v0,v1);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return unsigned_cmp(v0,v1);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_cmpgt_epi8 (v0,v1);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return unsigned_cmp(v0,v1);
        else  if constexpr(use_sse4 && c == category::int64x2  )  return _mm_cmpgt_epi64(v0,v1);
        else  if constexpr( c == category::int64x2  )             return map(is_greater, v0, v1);
        else  if constexpr( c == category::int32x4  )             return _mm_cmpgt_epi32(v0,v1);
        else  if constexpr( c == category::int16x8  )             return _mm_cmpgt_epi16(v0,v1);
        else  if constexpr( c == category::int8x16  )             return _mm_cmpgt_epi8 (v0,v1);
        else  if constexpr( c == category::uint64x2 )             return unsigned_cmp(v0,v1);
        else  if constexpr( c == category::uint32x4 )             return unsigned_cmp(v0,v1);
        else  if constexpr( c == category::uint16x8 )             return unsigned_cmp(v0,v1);
        else  if constexpr( c == category::uint8x16 )             return unsigned_cmp(v0,v1);
        else                                                      return aggregate(is_greater,v0,v1);
      }
    }
  }
}
