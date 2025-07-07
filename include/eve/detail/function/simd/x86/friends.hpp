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
}
