//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/allbits.hpp>

#include <type_traits>

namespace eve::detail
{
template<relative_conditional_expr C, scalar_value T,
         typename N,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void store_impl(sse2_, C const& cond, wide<T, N> const& v, Ptr ptr) noexcept
  requires x86_abi<abi_t<T, N>> && (!has_store_equivalent<wide<T, N>, Ptr>)
{
  if constexpr (std::same_as<C, ignore_none_>)
  {
    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( N::value * sizeof(T) == x86_512_::bytes )
      {
        if constexpr( std::is_same_v<T, double> ) _mm512_store_pd(ptr.get(), v);
        else if constexpr( std::is_same_v<T, float> ) _mm512_store_ps(ptr.get(), v);
        else if constexpr( std::is_integral_v<T> ) _mm512_store_si512((__m512i *)(ptr.get()), v);
      }
      else if constexpr( N::value * sizeof(T) == x86_256_::bytes )
      {
        if constexpr( std::is_same_v<T, double> ) _mm256_store_pd(ptr.get(), v);
        else if constexpr( std::is_same_v<T, float> ) _mm256_store_ps(ptr.get(), v);
        else if constexpr( std::is_integral_v<T> ) _mm256_store_si256((__m256i *)(ptr.get()), v);
      }
      else if constexpr( N::value * sizeof(T) == x86_128_::bytes )
      {
        if constexpr( std::is_same_v<T, double> ) _mm_store_pd(ptr.get(), v);
        else if constexpr( std::is_same_v<T, float> ) _mm_store_ps(ptr.get(), v);
        else if constexpr( std::is_integral_v<T> ) _mm_store_si128((__m128i *)(ptr.get()), v);
      }
      else { memcpy(ptr.get(), (T const *)(&v), N::value * sizeof(T)); }
    }
    else if constexpr( N::value * sizeof(T) == x86_512_::bytes )
    {
      if constexpr( std::is_same_v<T, double> ) _mm512_storeu_pd(ptr, v);
      else if constexpr( std::is_same_v<T, float> ) _mm512_storeu_ps(ptr, v);
      else if constexpr( std::is_integral_v<T> ) _mm512_storeu_si512((__m512i *)(ptr), v);
    }
    else if constexpr( N::value * sizeof(T) == x86_256_::bytes )
    {
      if constexpr( std::is_same_v<T, double> ) _mm256_storeu_pd(ptr, v);
      else if constexpr( std::is_same_v<T, float> ) _mm256_storeu_ps(ptr, v);
      else if constexpr( std::is_integral_v<T> ) _mm256_storeu_si256((__m256i *)(ptr), v);
    }
    else if constexpr( N::value * sizeof(T) == x86_128_::bytes )
    {
      if constexpr( std::is_same_v<T, double> ) _mm_storeu_pd(ptr, v);
      else if constexpr( std::is_same_v<T, float> ) _mm_storeu_ps(ptr, v);
      else if constexpr( std::is_integral_v<T> ) _mm_storeu_si128((__m128i *)(ptr), v);
    }
    else { memcpy(ptr, (T const *)(&v), N::value * sizeof(T)); }
  }
  else if constexpr( C::is_complete || C::has_alternative ) store_common(cpu_{}, cond, v, ptr);
  else if constexpr( (current_api == eve::avx || current_api == eve::avx2) && sizeof(T) >= 4 )
  {
    if constexpr( !std::is_pointer_v<Ptr> ) store[cond](v, ptr.get());
    else if constexpr( current_api == eve::avx && std::is_integral_v<T> )
    {
      using float_t      = detail::make_floating_point_t<sizeof(T)>;
      using wide_float_t = as_wide_t<float_t, N>;
      store[cond](eve::bit_cast(v, as<wide_float_t> {}), (float_t *)ptr);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto m = cond.mask(as<as_integer_t<wide<T, N>>> {});

      if constexpr( c == category::float64x2 ) _mm_maskstore_pd(ptr, m, v);
      else if constexpr( c == category::float64x4 ) _mm256_maskstore_pd(ptr, m, v);
      else if constexpr( c == category::float32x4 ) _mm_maskstore_ps(ptr, m, v);
      else if constexpr( c == category::float32x8 ) _mm256_maskstore_ps(ptr, m, v);
      else if constexpr( match(c, category::int64x2, category::uint64x2) )
        _mm_maskstore_epi64((long long *)ptr, m, v);
      else if constexpr( match(c, category::int64x4, category::uint64x4) )
        _mm256_maskstore_epi64((long long *)ptr, m, v);
      else if constexpr( match(c, category::int32x4, category::uint32x4) )
        _mm_maskstore_epi32((std::int32_t *)ptr, m, v);
      else if constexpr( match(c, category::int32x8, category::uint32x8) )
        _mm256_maskstore_epi32((std::int32_t *)ptr, m, v);
    }
  }
  else if constexpr( current_api >= eve::avx512 && !std::is_pointer_v<Ptr> )
  {
    if constexpr( Ptr::alignment() < 16 || sizeof(T) < 4 ) store[cond](v, ptr.get());
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto m = cond.mask(as(v)).storage().value;

      if constexpr( c == category::float64x2 ) _mm_mask_store_pd(ptr.get(), m, v);
      else if constexpr( c == category::float64x4 ) _mm256_mask_store_pd(ptr.get(), m, v);
      else if constexpr( c == category::float64x8 ) _mm512_mask_store_pd(ptr.get(), m, v);
      else if constexpr( c == category::float32x4 ) _mm_mask_store_ps(ptr.get(), m, v);
      else if constexpr( c == category::float32x8 ) _mm256_mask_store_ps(ptr.get(), m, v);
      else if constexpr( c == category::float32x16 ) _mm512_mask_store_ps(ptr.get(), m, v);
      else if constexpr( match(c, category::int64x2, category::uint64x2) )
        _mm_mask_store_epi64(ptr.get(), m, v);
      else if constexpr( match(c, category::int64x4, category::uint64x4) )
        _mm256_mask_store_epi64(ptr.get(), m, v);
      else if constexpr( match(c, category::int64x8, category::uint64x8) )
        _mm512_mask_store_epi64(ptr.get(), m, v);
      else if constexpr( match(c, category::int32x4, category::uint32x4) )
        _mm_mask_store_epi32(ptr.get(), m, v);
      else if constexpr( match(c, category::int32x8, category::uint32x8) )
        _mm256_mask_store_epi32(ptr.get(), m, v);
      else if constexpr( match(c, category::int32x16, category::uint32x16) )
        _mm512_mask_store_epi32(ptr.get(), m, v);
    }
  }
  else if constexpr( current_api >= eve::avx512 )
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto m = cond.mask(as(v)).storage().value;

    if constexpr( c == category::float64x2 ) _mm_mask_storeu_pd(ptr, m, v);
    else if constexpr( c == category::float64x4 ) _mm256_mask_storeu_pd(ptr, m, v);
    else if constexpr( c == category::float64x8 ) _mm512_mask_storeu_pd(ptr, m, v);
    else if constexpr( c == category::float32x4 ) _mm_mask_storeu_ps(ptr, m, v);
    else if constexpr( c == category::float32x8 ) _mm256_mask_storeu_ps(ptr, m, v);
    else if constexpr( c == category::float32x16 ) _mm512_mask_storeu_ps(ptr, m, v);
    else if constexpr( match(c, category::int64x2, category::uint64x2) )
      _mm_mask_storeu_epi64(ptr, m, v);
    else if constexpr( match(c, category::int64x4, category::uint64x4) )
      _mm256_mask_storeu_epi64(ptr, m, v);
    else if constexpr( match(c, category::int64x8, category::uint64x8) )
      _mm512_mask_storeu_epi64(ptr, m, v);
    else if constexpr( match(c, category::int32x4, category::uint32x4) )
      _mm_mask_storeu_epi32(ptr, m, v);
    else if constexpr( match(c, category::int32x8, category::uint32x8) )
      _mm256_mask_storeu_epi32(ptr, m, v);
    else if constexpr( match(c, category::int32x16, category::uint32x16) )
      _mm512_mask_storeu_epi32(ptr, m, v);
    else if constexpr( match(c, category::int16x8, category::uint16x8) )
      _mm_mask_storeu_epi16(ptr, m, v);
    else if constexpr( match(c, category::int16x16, category::uint16x16) )
      _mm256_mask_storeu_epi16(ptr, m, v);
    else if constexpr( match(c, category::int16x32, category::uint16x32) )
      _mm512_mask_storeu_epi16(ptr, m, v);
    else if constexpr( match(c, category::int8x16, category::uint8x16) )
      _mm_mask_storeu_epi8(ptr, m, v);
    else if constexpr( match(c, category::int8x32, category::uint8x32) )
      _mm256_mask_storeu_epi8(ptr, m, v);
    else if constexpr( match(c, category::int8x64, category::uint8x64) )
      _mm512_mask_storeu_epi8(ptr, m, v);
  }
  else store_common(cpu_{}, cond, v, ptr);
}

}
