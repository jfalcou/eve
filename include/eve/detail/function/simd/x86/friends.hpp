//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_floating_point.hpp>

namespace eve::detail
{
//================================================================================================
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_eq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::eq_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpeq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpeq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpeq_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpeq_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpeq_pd(v, w);
    else
    {
      constexpr auto use_avx2 = current_api >= avx2;
      constexpr auto eq       = []<typename E>(E const& ev, E const& fv)
      { return as_logical_t<E>(ev == fv); };

      if constexpr( use_avx2 && c == category::int64x4 ) return _mm256_cmpeq_epi64(v, w);
      else if constexpr( use_avx2 && c == category::uint64x4 ) return _mm256_cmpeq_epi64(v, w);
      else if constexpr( use_avx2 && c == category::int32x8 ) return _mm256_cmpeq_epi32(v, w);
      else if constexpr( use_avx2 && c == category::uint32x8 ) return _mm256_cmpeq_epi32(v, w);
      else if constexpr( use_avx2 && c == category::int16x16 ) return _mm256_cmpeq_epi16(v, w);
      else if constexpr( use_avx2 && c == category::uint16x16 ) return _mm256_cmpeq_epi16(v, w);
      else if constexpr( use_avx2 && c == category::int8x32 ) return _mm256_cmpeq_epi8(v, w);
      else if constexpr( use_avx2 && c == category::uint8x32 ) return _mm256_cmpeq_epi8(v, w);
      else if constexpr( c == category::int64x2 )
      {
        if constexpr( N::value == 2 )
          return as_logical_t<wide<T, N>> {v.get(0) == w.get(0), v.get(1) == w.get(1)};
        else return as_logical_t<wide<T, N>> {v.get(0) == w.get(0)};
      }
      else if constexpr( c == category::int32x4 ) return _mm_cmpeq_epi32(v, w);
      else if constexpr( c == category::int16x8 ) return _mm_cmpeq_epi16(v, w);
      else if constexpr( c == category::int8x16 ) return _mm_cmpeq_epi8(v, w);
      else if constexpr( c == category::uint64x2 )
      {
        if constexpr( N::value == 2 )
          return as_logical_t<wide<T, N>> {v.get(0) == w.get(0), v.get(1) == w.get(1)};
        else return as_logical_t<wide<T, N>> {v.get(0) == w.get(0)};
      }
      else if constexpr( c == category::uint32x4 ) return _mm_cmpeq_epi32(v, w);
      else if constexpr( c == category::uint16x8 ) return _mm_cmpeq_epi16(v, w);
      else if constexpr( c == category::uint8x16 ) return _mm_cmpeq_epi8(v, w);
      else return aggregate(eq, v, w);
    }
  }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( !abi_t<T, N>::is_wide_logical )
  {
    return logical<wide<T, N>> {~(v.storage() ^ w.storage())};
  }
  else
  {
    // AVX has a bad == for integers so we use XOR
    if constexpr( current_api == avx ) return bit_cast(~v.bits() ^ w.bits(), as(v));
    else return bit_cast(v.bits() == w.bits(), as(v));
  }
}

//================================================================================================
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_neq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::neq_uq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpneq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpneq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpneq_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpneq_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpneq_pd(v, w);
    else return !(v == w);
  }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( !abi_t<T, N>::is_wide_logical )
  {
    return logical<wide<T, N>> {v.storage() ^ w.storage()};
  }
  else { return bit_cast(v.bits() ^ w.bits(), as(v)); }
}

//================================================================================================
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_geq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::ge_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpge_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpge_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpge_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpge_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpge_pd(v, w);
    else return !(v < w);
  }
}

//================================================================================================
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_leq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::le_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmple_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmple_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmple_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmple_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmple_pd(v, w);
    else return !(v > w);
  }
}
}
