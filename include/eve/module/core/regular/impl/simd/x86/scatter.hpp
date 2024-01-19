//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename Idx, typename Ptr, callable_options O>
  EVE_FORCEINLINE void
  scatter_(EVE_REQUIRES(avx512_), O const& opts, wide<T,N> const& v, Ptr ptr, Idx const& idx) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    // Unsupported value types go back to emulation
    if      constexpr(sizeof(T) < 4)                    scatter_(EVE_TARGETS(cpu_), opts, v, ptr, idx);
    // Small indexes are converted to int32
    else if constexpr(sizeof(element_type_t<Idx>) < 4)  scatter[opts](v, ptr, convert(idx, as<std::int32_t>{}));
    else
    {
      // Use intrinsics
      constexpr auto c = categorize<wide<T, N>>();

      if constexpr(sizeof(element_type_t<Idx>) == 4)
      {
        if      constexpr(match(c, category::int32x16, category::uint32x16))  _mm512_i32scatter_epi32(ptr, idx, v, 4);
        else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm256_i32scatter_epi32(ptr, idx, v, 4);
        else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_i32scatter_epi32   (ptr, idx, v, 4);
        else if constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_i32scatter_epi64(ptr, idx, v, 8);
        else if constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_i32scatter_epi64(ptr, idx, v, 8);
        else if constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_i32scatter_epi64   (ptr, idx, v, 8);
        else if constexpr(c == category::float32x16 )                         _mm512_i32scatter_ps   (ptr, idx, v, 4);
        else if constexpr(c == category::float32x8  )                         _mm256_i32scatter_ps   (ptr, idx, v, 4);
        else if constexpr(c == category::float32x4  )                         _mm_i32scatter_ps      (ptr, idx, v, 4);
        else if constexpr(c == category::float64x8  )                         _mm512_i32scatter_pd   (ptr, idx, v, 8);
        else if constexpr(c == category::float64x4  )                         _mm256_i32scatter_pd   (ptr, idx, v, 8);
        else if constexpr(c == category::float64x2  )                         _mm_i32scatter_pd      (ptr, idx, v, 8);
      }
      else if constexpr(sizeof(element_type_t<Idx>) == 8)
      {
        if      constexpr(match(c, category::int32x16, category::uint32x16))  _mm512_i64scatter_epi32(ptr, idx, v, 4);
        else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm256_i64scatter_epi32(ptr, idx, v, 4);
        else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_i64scatter_epi32   (ptr, idx, v, 4);
        else if constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_i64scatter_epi64(ptr, idx, v, 8);
        else if constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_i64scatter_epi64(ptr, idx, v, 8);
        else if constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_i64scatter_epi64   (ptr, idx, v, 8);
        else if constexpr(c == category::float32x16 )                         _mm512_i64scatter_ps   (ptr, idx, v, 4);
        else if constexpr(c == category::float32x8  )                         _mm256_i64scatter_ps   (ptr, idx, v, 4);
        else if constexpr(c == category::float32x4  )                         _mm_i64scatter_ps      (ptr, idx, v, 4);
        else if constexpr(c == category::float64x8  )                         _mm512_i64scatter_pd   (ptr, idx, v, 8);
        else if constexpr(c == category::float64x4  )                         _mm256_i64scatter_pd   (ptr, idx, v, 8);
        else if constexpr(c == category::float64x2  )                         _mm_i64scatter_pd      (ptr, idx, v, 8);
      }
    }
  }

  // template<simd_value T, integral_simd_value Idx, simd_compatible_ptr<T> Ptr, conditional_expr C, callable_options O>
  // EVE_FORCEINLINE void
  // scatter_(EVE_REQUIRES(avx512_), C const& mask, O const&,  wide<T, N> const& v) noexcept requires x86_abi<abi_t<T, N>>
  // {
  //   auto const            s = alternative(mask, v, as(v));
  //   [[maybe_unused]] auto m = expand_mask(mask, as(v)).storage().value;
  //   constexpr auto        c = categorize<wide<T, N>>();

  //   if      constexpr( C::is_complete )               return s;
  //   else if constexpr( match(c, category::unsigned_)) return if_else(mask, v, s);
  //   else if constexpr( c == category::float32x16    ) return _mm512_mask_abs_ps(s, m, v);
  //   else if constexpr( c == category::float64x8     ) return _mm512_mask_abs_pd(s, m, v);
  //   else if constexpr( match(c, category::float_)   ) return if_else(mask, eve::abs(v), s);
  //   else if constexpr( c == category::int64x8       ) return _mm512_mask_abs_epi64(s, m, v);
  //   else if constexpr( c == category::int64x4       ) return _mm256_mask_abs_epi64(s, m, v);
  //   else if constexpr( c == category::int64x2       ) return _mm_mask_abs_epi64   (s, m, v);
  //   else if constexpr( c == category::int32x16      ) return _mm512_mask_abs_epi32(s, m, v);
  //   else if constexpr( c == category::int32x8       ) return _mm256_mask_abs_epi32(s, m, v);
  //   else if constexpr( c == category::int32x4       ) return _mm_mask_abs_epi32   (s, m, v);
  //   else if constexpr( c == category::int16x32      ) return _mm512_mask_abs_epi16(s, m, v);
  //   else if constexpr( c == category::int16x16      ) return _mm256_mask_abs_epi16(s, m, v);
  //   else if constexpr( c == category::int16x8       ) return _mm_mask_abs_epi16   (s, m, v);
  //   else if constexpr( c == category::int8x64       ) return _mm512_mask_abs_epi8 (s, m, v);
  //   else if constexpr( c == category::int8x32       ) return _mm256_mask_abs_epi8 (s, m, v);
  //   else if constexpr( c == category::int8x16       ) return _mm_mask_abs_epi8    (s, m, v);
  // }
}
