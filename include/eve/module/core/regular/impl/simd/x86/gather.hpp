//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<typename U, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(avx2_), U const* p, wide<T, N> v) noexcept -> wide<U, N>
requires x86_abi<abi_t<T, N>>
{
  // Aggregation cases
  if      constexpr(has_aggregated_abi_v<wide<U, N>>)
  {
    auto[l,h] = v.slice();
    return wide<U,N>(gather(p,l),gather(p,h));
  }
  // Smaller data goes through the generic cases
  else if constexpr(sizeof(U) <= 2)           return gather_(EVE_RETARGET(cpu_), p, v);
  // Small index get converted then we recall gather
  else if constexpr(sizeof(T) <  4)           return gather(p, convert(v, as<std::int32_t>{}));
  // AVX2 code is exactly similar to masked one + ignore_none
  else if constexpr( current_api == avx2 )    return gather[ignore_none](p,v);
  else if constexpr( current_api == avx512 )
  {
    using enum category;
    constexpr auto i = categorize<wide<T, N>>();
    constexpr auto c = categorize<wide<U, N>>();

    constexpr bool i_32x8   = match(i, int32x8 , uint32x8);
    constexpr bool i_32x16  = match(i, int32x16, uint32x16);
    constexpr bool i_64x8   = match(i, int64x8 , uint64x8);

    constexpr bool d_i32x8  = match(c, int32x8 , uint32x8);
    constexpr bool d_i32x16 = match(c, int32x16, uint32x16);
    constexpr bool d_i64x8  = match(c, int64x8 , uint64x8);

    if      constexpr(i_32x8  && d_i64x8        ) return _mm512_i32gather_epi64(v, p, 8);
    else if constexpr(i_32x16 && d_i32x16       ) return _mm512_i32gather_epi32(v, p, 4);
    else if constexpr(i_64x8  && d_i64x8        ) return _mm512_i64gather_epi64(v, p, 8);
    else if constexpr(i_64x8  && d_i32x8        ) return _mm512_i64gather_epi32(v, p, 4);
    else if constexpr(i_32x8  && c == float64x8 ) return _mm512_i32gather_pd   (v, p, 8);
    else if constexpr(i_64x8  && c == float64x8 ) return _mm512_i64gather_pd   (v, p, 8);
    else if constexpr(i_32x16 && c == float32x16) return _mm512_i32gather_ps   (v, p, 4);
    else if constexpr(i_64x8  && c == float32x8 ) return _mm512_i64gather_ps   (v, p, 4);
    else                                          return gather[ignore_none](p,v);
  }
}

template<typename U, conditional_expr C, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(avx2_), C cx, U const* p, wide<T, N> v) noexcept -> wide<U, N>
requires x86_abi<abi_t<T, N>>
{
  using enum category;
  constexpr auto i = categorize<wide<T, N>>();
  constexpr auto c = categorize<wide<U, N>>();

  constexpr bool i_32x4   = match(i, int32x4 , uint32x4);
  constexpr bool i_32x8   = match(i, int32x8 , uint32x8);
  constexpr bool i_64x2   = match(i, int64x2 , uint64x2);
  constexpr bool i_64x4   = match(i, int64x4 , uint64x4);

  constexpr bool d_i32x4  = match(c, int32x4 , uint32x4);
  constexpr bool d_i32x8  = match(c, int32x8 , uint32x8);
  constexpr bool d_i64x2  = match(c, int64x2 , uint64x2);
  constexpr bool d_i64x4  = match(c, int64x4 , uint64x4);

  // Smaller data goes through the generic cases
  if      constexpr(sizeof(U) <= 2)           return gather_(EVE_RETARGET(cpu_), cx, p, v);
  // Small index get converted then we recall gather
  else if constexpr(sizeof(T) <  4)           return gather[cx](p, convert(v, as<std::int32_t>{}));
  else if constexpr( current_api == avx2 )
  {
    using pl_t = long long const*;
    using pi_t = int const*;
    auto s = alternative(cx, wide<U, N>{}, as<wide<U, N>> {});
    auto m = expand_mask(cx, as<wide<U, N>> {});

    if      constexpr(i_32x4 && d_i64x2       ) return _mm_mask_i32gather_epi64   (s,pl_t(p),v,m,8);
    else if constexpr(i_64x2 && d_i64x2       ) return _mm_mask_i64gather_epi64   (s,pl_t(p),v,m,8);
    else if constexpr(i_32x4 && d_i64x4       ) return _mm256_mask_i32gather_epi64(s,pl_t(p),v,m,8);
    else if constexpr(i_64x4 && d_i64x4       ) return _mm256_mask_i64gather_epi64(s,pl_t(p),v,m,8);
    else if constexpr(i_32x4 && d_i32x4       ) return _mm_mask_i32gather_epi32   (s,pi_t(p),v,m,4);
    else if constexpr(i_64x2 && d_i32x4       ) return _mm_mask_i64gather_epi32   (s,pi_t(p),v,m,4);
    else if constexpr(i_32x8 && d_i32x8       ) return _mm256_mask_i32gather_epi32(s,pi_t(p),v,m,4);
    else if constexpr(i_64x4 && d_i32x4       ) return _mm256_mask_i64gather_epi32(s,pi_t(p),v,m,4);
    else if constexpr(i_32x4 && c == float64x2) return _mm_mask_i32gather_pd      (s,p,v,m,8);
    else if constexpr(i_64x2 && c == float64x2) return _mm_mask_i64gather_pd      (s,p,v,m,8);
    else if constexpr(i_32x4 && c == float64x4) return _mm256_mask_i32gather_pd   (s,p,v,m,8);
    else if constexpr(i_64x4 && c == float64x4) return _mm256_mask_i64gather_pd   (s,p,v,m,8);
    else if constexpr(i_32x4 && c == float32x4) return _mm_mask_i32gather_ps      (s,p,v,m,4);
    else if constexpr(i_64x2 && c == float32x4) return _mm_mask_i64gather_ps      (s,p,v,m,4);
    else if constexpr(i_32x8 && c == float32x8) return _mm256_mask_i32gather_ps   (s,p,v,m,4);
    else if constexpr(i_64x4 && c == float32x4) return _mm256_mask_i64gather_ps   (s,p,v,m,4);
  }
  else if constexpr( current_api == avx512 )
  {
    // Complete exact AVX512 type just call gather back
    // The sizeof test prevents circular call on AVX2 types in AVX512 mode
    if constexpr(C::is_complete && sizeof(v) == 64) return gather(p, v);
    else
    {
      constexpr bool i_32x16  = match(i, int32x16, uint32x16);
      constexpr bool i_64x8   = match(i, int64x8 , uint64x8);
      constexpr bool d_i32x16 = match(c, int32x16, uint32x16);
      constexpr bool d_i64x8  = match(c, int64x8 , uint64x8);

      auto s = alternative(cx, wide<U, N>{}, as<wide<U, N>> {});
      auto m = expand_mask(cx, as<wide<U, N>> {}).storage().value;

      if      constexpr(i_32x8  && d_i64x8 )        return _mm512_mask_i32gather_epi64 (s,m,v,p,8);
      else if constexpr(i_32x4  && d_i64x2 )        return _mm_mmask_i32gather_epi64   (s,m,v,p,8);
      else if constexpr(i_32x4  && d_i64x4 )        return _mm256_mmask_i32gather_epi64(s,m,v,p,8);
      else if constexpr(i_64x8  && d_i64x8 )        return _mm512_mask_i64gather_epi64 (s,m,v,p,8);
      else if constexpr(i_64x4  && d_i64x4 )        return _mm256_mmask_i64gather_epi64(s,m,v,p,8);
      else if constexpr(i_64x2  && d_i64x2 )        return _mm_mmask_i64gather_epi64   (s,m,v,p,8);
      else if constexpr(i_32x16 && d_i32x16)        return _mm512_mask_i32gather_epi32 (s,m,v,p,4);
      else if constexpr(i_32x8  && d_i32x8 )        return _mm256_mmask_i32gather_epi32(s,m,v,p,4);
      else if constexpr(i_32x4  && d_i32x4 )        return _mm_mmask_i32gather_epi32   (s,m,v,p,4);
      else if constexpr(i_64x8  && d_i32x8 )        return _mm512_mask_i64gather_epi32 (s,m,v,p,4);
      else if constexpr(i_64x4  && d_i32x4 )        return _mm256_mmask_i64gather_epi32(s,m,v,p,4);
      else if constexpr(i_64x2  && d_i32x4 )        return _mm_mmask_i64gather_epi32   (s,m,v,p,4);
      else if constexpr(i_32x8  && c == float64x8 ) return _mm512_mask_i32gather_pd    (s,m,v,p,8);
      else if constexpr(i_32x4  && c == float64x4 ) return _mm256_mmask_i32gather_pd   (s,m,v,p,8);
      else if constexpr(i_32x4  && c == float64x2 ) return _mm_mmask_i32gather_pd      (s,m,v,p,8);
      else if constexpr(i_64x8  && c == float64x8 ) return _mm512_mask_i64gather_pd    (s,m,v,p,8);
      else if constexpr(i_64x4  && c == float64x4 ) return _mm256_mmask_i64gather_pd   (s,m,v,p,8);
      else if constexpr(i_64x2  && c == float64x2 ) return _mm_mmask_i64gather_pd      (s,m,v,p,8);
      else if constexpr(i_32x16 && c == float32x16) return _mm512_mask_i32gather_ps    (s,m,v,p,4);
      else if constexpr(i_32x8  && c == float32x8 ) return _mm256_mmask_i32gather_ps   (s,m,v,p,4);
      else if constexpr(i_32x4  && c == float32x4 ) return _mm_mmask_i32gather_ps      (s,m,v,p,4);
      else if constexpr(i_64x8  && c == float32x8 ) return _mm512_mask_i64gather_ps    (s,m,v,p,4);
      else if constexpr(i_64x4  && c == float32x4 ) return _mm256_mmask_i64gather_ps   (s,m,v,p,4);
      else if constexpr(i_64x2  && c == float32x4 ) return _mm_mmask_i64gather_ps      (s,m,v,p,4);
    }
  }
}
}
