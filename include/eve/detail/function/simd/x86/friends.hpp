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

#include <eve/arch/as_register.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_lognot(logical<wide<T, N, ABI>> const& v) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using m_t = typename logical<wide<T, N, ABI>>::storage_type;
      return m_t(~v.storage().value);
    }
    else
    {
      return bit_cast(~v.bits(), as(v));
    }
  }

  //================================================================================================
  // operator== implementation
  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_eq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::eq_oq);

    if constexpr( !ABI::is_wide_logical )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f )};
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f )};
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f )};
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f )};
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f )};
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f )};
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpeq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpeq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpeq_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpeq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpeq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpeq_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpeq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpeq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpeq_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpeq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpeq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpeq_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpeq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpeq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpeq_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpeq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpeq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpeq_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpeq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpeq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpeq_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpeq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpeq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpeq_epi8_mask    (v,w)};
    }
    else
    {
      constexpr auto f = to_integer(cmp_flt::eq_oq);

            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpeq_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpeq_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comeq_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comeq_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comeq_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comeq_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comeq_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comeq_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comeq_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comeq_epi8 (v,w);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        constexpr auto eq = []<typename E>(E e, E f) { return as_logical_t<E>(e == f); };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_cmpeq_epi64(v,w);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return _mm256_cmpeq_epi64(v,w);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_cmpeq_epi32(v,w);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return _mm256_cmpeq_epi32(v,w);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_cmpeq_epi16(v,w);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return _mm256_cmpeq_epi16(v,w);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_cmpeq_epi8 (v,w);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return _mm256_cmpeq_epi8 (v,w);
        else  if constexpr( c == category::int64x2  )             return map(eq,v,w);
        else  if constexpr( c == category::int32x4  )             return _mm_cmpeq_epi32(v,w);
        else  if constexpr( c == category::int16x8  )             return _mm_cmpeq_epi16(v,w);
        else  if constexpr( c == category::int8x16  )             return _mm_cmpeq_epi8 (v,w);
        else  if constexpr( c == category::uint64x2 )             return map(eq,v,w);
        else  if constexpr( c == category::uint32x4 )             return _mm_cmpeq_epi32(v,w);
        else  if constexpr( c == category::uint16x8 )             return _mm_cmpeq_epi16(v,w);
        else  if constexpr( c == category::uint8x16 )             return _mm_cmpeq_epi8 (v,w);
        else                                                      return aggregate(eq,v,w);
      }
    }
  }

  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_eq(logical<wide<T,N,ABI>> v, logical<wide<T,N,ABI>> w) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using s_t = typename logical<wide<T,N,ABI>>::storage_type;
      return logical<wide<T,N,ABI>>{ s_t(~(v.storage().value ^ w.storage().value)) };
    }
    else
    {
      return bit_cast(v.bits() == w.bits(), as(v));
    }
  }
}
