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

  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

    [[maybe_unused]] auto shft = [](auto a, auto b )
    {
      static constexpr auto half_size = (N::value/2 > 0) ? N::value/2 : 1;
      using i16_t = wide<std::uint16_t, fixed<half_size>>;

      i16_t const masklow(0xff);
      i16_t const maskhi (0xff00);
      auto const xx   =  bit_cast(a, as<i16_t>());
      auto const odd  = (xx << b) & masklow;
      auto const even = ((xx & maskhi) << b) & maskhi;

      return bit_cast(odd+even, as(a));
    };

          if constexpr( c == category::int64x8  ) v = _mm512_slli_epi64(v,s);
    else  if constexpr( c == category::int32x16 ) v = _mm512_slli_epi32(v,s);
    else  if constexpr( c == category::int16x32 ) v = _mm512_slli_epi16(v,s);
    else  if constexpr( c == category::uint64x8 ) v = _mm512_slli_epi64(v,s);
    else  if constexpr( c == category::uint32x16) v = _mm512_slli_epi32(v,s);
    else  if constexpr( c == category::uint16x32) v = _mm512_slli_epi16(v,s);
    else  if constexpr( c == category::int8x16  && N::value != 1) v = shft(v,s);
    else  if constexpr( c == category::uint8x16 && N::value != 1) v = shft(v,s);
    else  if constexpr( c == category::int64x2  ) v = _mm_slli_epi64(v,s);
    else  if constexpr( c == category::uint64x2 ) v = _mm_slli_epi64(v,s);
    else  if constexpr( c == category::int32x4  ) v = _mm_slli_epi32(v,s);
    else  if constexpr( c == category::uint32x4 ) v = _mm_slli_epi32(v,s);
    else  if constexpr( c == category::int16x8  ) v = _mm_slli_epi16(v,s);
    else  if constexpr( c == category::uint16x8 ) v = _mm_slli_epi16(v,s);
    else  if constexpr( sizeof(v) == 32 )
    {
      if constexpr( is_avx2 )
      {
              if constexpr( c == category::int64x4  ) v = _mm256_slli_epi64(v,s);
        else  if constexpr( c == category::int32x8  ) v = _mm256_slli_epi32(v,s);
        else  if constexpr( c == category::int16x16 ) v = _mm256_slli_epi16(v,s);
        else  if constexpr( c == category::int8x32  ) v = shft(v,s);
        else  if constexpr( c == category::uint64x4 ) v = _mm256_slli_epi64(v,s);
        else  if constexpr( c == category::uint32x8 ) v = _mm256_slli_epi32(v,s);
        else  if constexpr( c == category::uint16x16) v = _mm256_slli_epi16(v,s);
        else  if constexpr( c == category::uint8x32 ) v = shft(v,s);
      }
      else
      {
        auto[la,ha] = v.slice();
        la <<= s;
        ha <<= s;
        v = wide<T,N>{la,ha};
      }
    }
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a << b); }, v, s);
    }

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

    [[maybe_unused]] auto shft = []<typename V>(V a, auto b)
    {
      auto[la,ha] = a.slice();
      auto[lb,hb] = b.slice();

      la <<= lb;
      ha <<= hb;

      return  V{la,ha};
    };

          if constexpr( is_avx2 && c == category::int64x4  ) v = _mm256_sllv_epi64(v, s);
    else  if constexpr( is_avx2 && c == category::int32x8  ) v = _mm256_sllv_epi32(v, s);
    else  if constexpr( is_avx2 && c == category::uint64x4 ) v = _mm256_sllv_epi64(v, s);
    else  if constexpr( is_avx2 && c == category::uint32x8 ) v = _mm256_sllv_epi32(v, s);
    else  if constexpr(            c == category::int64x8  ) v = _mm512_sllv_epi64(v, s);
    else  if constexpr(            c == category::int32x16 ) v = _mm512_sllv_epi32(v, s);
    else  if constexpr(            c == category::int16x32 ) v = _mm512_sllv_epi16(v, s);
    else  if constexpr(            c == category::uint64x8 ) v = _mm512_sllv_epi64(v, s);
    else  if constexpr(            c == category::uint32x16) v = _mm512_sllv_epi32(v, s);
    else  if constexpr(            c == category::uint16x32) v = _mm512_sllv_epi16(v, s);
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a << b); }, v, s);
    }

    return v;
  }
}
