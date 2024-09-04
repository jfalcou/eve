//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c          = categorize<wide<T, N>>();
    constexpr bool is_avx2    = current_api >= avx2;
    constexpr bool is_avx512  = current_api >= avx512;

          if constexpr(              c == category::int64x8  ) v = _mm512_srai_epi64(v,s);
    else  if constexpr(              c == category::int32x16 ) v = _mm512_srai_epi32(v,s);
    else  if constexpr(              c == category::int16x32 ) v = _mm512_srai_epi16(v,s);
    else  if constexpr(              c == category::uint64x8 ) v = _mm512_srli_epi64(v,s);
    else  if constexpr(              c == category::uint32x16) v = _mm512_srli_epi32(v,s);
    else  if constexpr(              c == category::uint16x32) v = _mm512_srli_epi16(v,s);
    else  if constexpr( is_avx2   && c == category::int32x8  ) v = _mm256_srai_epi32(v,s);
    else  if constexpr( is_avx2   && c == category::int16x16 ) v = _mm256_srai_epi16(v,s);
    else  if constexpr( is_avx2   && c == category::uint64x4 ) v = _mm256_srli_epi64(v,s);
    else  if constexpr( is_avx2   && c == category::uint32x8 ) v = _mm256_srli_epi32(v,s);
    else  if constexpr( is_avx2   && c == category::uint16x16) v = _mm256_srli_epi16(v,s);
    else  if constexpr( is_avx512 && c == category::int64x2  ) v = _mm_srai_epi64(v,s);
    else  if constexpr(              c == category::int32x4  ) v = _mm_srai_epi32(v,s);
    else  if constexpr(              c == category::int16x8  ) v = _mm_srai_epi16(v,s);
    else  if constexpr(              c == category::uint64x2 ) v = _mm_srli_epi64(v,s);
    else  if constexpr(              c == category::uint32x4 ) v = _mm_srli_epi32(v,s);
    else  if constexpr(              c == category::uint16x8 ) v = _mm_srli_epi16(v,s);
    else
    {
      v = map( []<typename V>(V const& a, auto b) { return static_cast<V>(a >> b); }, v, s);
    }

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, wide<U,N> s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c         = categorize<wide<T, N>>();
    constexpr bool is_avx2   = current_api >= avx2;
    constexpr bool is_avx512 = current_api >= avx512;

    [[maybe_unused]] auto shft = []<typename V>(V a, auto b)
    {
      auto[la,ha] = a.slice();
      auto[lb,hb] = b.slice();

      la >>= lb;
      ha >>= hb;

      return  V{la,ha};
    };

          if constexpr( is_avx512    && c == category::int64x2  ) v = _mm_srav_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::int32x4  ) v = _mm_srav_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::int16x8  ) v = _mm_srav_epi16(v, s);
    else  if constexpr( is_avx2      && c == category::uint64x2 ) v = _mm_srlv_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::uint32x4 ) v = _mm_srlv_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::uint16x8 ) v = _mm_srlv_epi16(v, s);
    else  if constexpr( is_avx512    && c == category::int64x4  ) v = _mm256_srav_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::int32x8  ) v = _mm256_srav_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::int16x16 ) v = _mm256_srav_epi16(v, s);
    else  if constexpr( is_avx2      && c == category::uint64x4 ) v = _mm256_srlv_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::uint32x8 ) v = _mm256_srlv_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::uint16x16) v = _mm256_srlv_epi16(v, s);
    else  if constexpr(                 c == category::int64x8  ) v = _mm512_srav_epi64(v, s);
    else  if constexpr(                 c == category::int32x16 ) v = _mm512_srav_epi32(v, s);
    else  if constexpr(                 c == category::int16x32 ) v = _mm512_srav_epi16(v, s);
    else  if constexpr(                 c == category::uint64x8 ) v = _mm512_srlv_epi64(v, s);
    else  if constexpr(                 c == category::uint32x16) v = _mm512_srlv_epi32(v, s);
    else  if constexpr(                 c == category::uint16x32) v = _mm512_srlv_epi16(v, s);
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a >> b); }, v, s);
    }

    return v;
  }
}
