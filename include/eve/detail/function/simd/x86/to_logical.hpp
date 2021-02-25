//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T,N,ABI>> to_logical( wide<T,N,ABI> const& v ) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    [[maybe_unused]] wide<T,N,ABI> const z{0};

    if constexpr( current_api >= avx512 )
    {
      constexpr auto m = fpclass::poszero | fpclass::negzero;

      using storage_t = typename logical<wide<T, N, ABI>>::storage_type;
      using i_t       = typename storage_t::type;

            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmpneq_ps_mask(v,z)};
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmpneq_pd_mask(v,z)};
      else  if constexpr( c == category::float32x8  ) return mask8 {~i_t(_mm256_fpclass_ps_mask(v, m))};
      else  if constexpr( c == category::float64x4  ) return mask8 {~i_t(_mm256_fpclass_pd_mask(v, m))};
      else  if constexpr( c == category::float32x4  ) return mask8 {~i_t(_mm_fpclass_ps_mask   (v, m))};
      else  if constexpr( c == category::float64x2  ) return mask8 {~i_t(_mm_fpclass_pd_mask   (v, m))};
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpneq_epu64_mask(v,z)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpneq_epu64_mask(v,z)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpneq_epu64_mask   (v,z)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpneq_epu32_mask(v,z)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpneq_epu32_mask(v,z)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpneq_epu32_mask   (v,z)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpneq_epu16_mask(v,z)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpneq_epu16_mask(v,z)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpneq_epu16_mask   (v,z)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpneq_epu8_mask (v,z)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpneq_epu8_mask (v,z)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpneq_epu8_mask    (v,z)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpneq_epi64_mask(v,z)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpneq_epi64_mask(v,z)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpneq_epi64_mask   (v,z)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpneq_epi32_mask(v,z)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpneq_epi32_mask(v,z)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpneq_epi32_mask   (v,z)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpneq_epi16_mask(v,z)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpneq_epi16_mask(v,z)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpneq_epi16_mask   (v,z)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpneq_epi8_mask (v,z)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpneq_epi8_mask (v,z)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpneq_epi8_mask    (v,z)};
    }
    else
    {
      constexpr auto f = to_integer(cmp_flt::neq_uq);

            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,z,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,z,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpneq_ps(v,z);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpneq_pd(v,z);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comneq_epu64(v,z);
        else  if constexpr( c == category::uint32x4 ) return _mm_comneq_epu32(v,z);
        else  if constexpr( c == category::uint16x8 ) return _mm_comneq_epu16(v,z);
        else  if constexpr( c == category::uint8x16 ) return _mm_comneq_epu8 (v,z);
        else  if constexpr( c == category::int64x2  ) return _mm_comneq_epi64(v,z);
        else  if constexpr( c == category::int32x4  ) return _mm_comneq_epi32(v,z);
        else  if constexpr( c == category::int16x8  ) return _mm_comneq_epi16(v,z);
        else  if constexpr( c == category::int8x16  ) return _mm_comneq_epi8 (v,z);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        [[maybe_unused]] auto const a = wide<T,N,ABI>(~0ULL);
        [[maybe_unused]] auto const nez = []<typename X>(X x)
        {
          if constexpr( scalar_value<X> ) return logical<T>(!!x);
          else                            return to_logical(x);
        };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_andnot_si256(_mm256_cmpeq_epi64(v,z), a);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return _mm256_andnot_si256(_mm256_cmpeq_epi64(v,z), a);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_andnot_si256(_mm256_cmpeq_epi32(v,z), a);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return _mm256_andnot_si256(_mm256_cmpeq_epi32(v,z), a);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_andnot_si256(_mm256_cmpeq_epi16(v,z), a);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return _mm256_andnot_si256(_mm256_cmpeq_epi16(v,z), a);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_andnot_si256(_mm256_cmpeq_epi8 (v,z), a);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return _mm256_andnot_si256(_mm256_cmpeq_epi8 (v,z), a);
        else  if constexpr( c == category::int64x2  )             return map(nez, v);
        else  if constexpr( c == category::int32x4  )             return _mm_andnot_si128(_mm_cmpeq_epi32(v,z), a);
        else  if constexpr( c == category::int16x8  )             return _mm_andnot_si128(_mm_cmpeq_epi16(v,z), a);
        else  if constexpr( c == category::int8x16  )             return _mm_andnot_si128(_mm_cmpeq_epi8 (v,z), a);
        else  if constexpr( c == category::uint64x2 )             return map(nez, v);
        else  if constexpr( c == category::uint32x4 )             return _mm_andnot_si128(_mm_cmpeq_epi32(v,z), a);
        else  if constexpr( c == category::uint16x8 )             return _mm_andnot_si128(_mm_cmpeq_epi16(v,z), a);
        else  if constexpr( c == category::uint8x16 )             return _mm_andnot_si128(_mm_cmpeq_epi8 (v,z), a);
        else                                                      return aggregate(nez,v);
      }
    }
  }
}
