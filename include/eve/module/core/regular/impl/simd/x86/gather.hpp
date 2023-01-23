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
  // Small index get converted then we recall gather
  if constexpr(sizeof(T) < 4)
  {
    return gather(p, convert(v, as<std::int32_t>{}));
  }
  else
  {
    using pl_t = long long const*;
    using pi_t = int const*;

    using enum category;
    constexpr auto i = categorize<wide<T, N>>();
    constexpr auto c = categorize<wide<U, N>>();

    constexpr bool i_32x4   = match(i, int32x4 , uint32x4);
    constexpr bool i_32x8   = match(i, int32x8 , uint32x8);
    constexpr bool i_32x16  = match(i, int32x16, uint32x16);
    constexpr bool i_64x2   = match(i, int64x2 , uint64x2);
    constexpr bool i_64x4   = match(i, int64x4 , uint64x4);
    constexpr bool i_64x8   = match(i, int64x8 , uint64x8);

    constexpr bool d_i32x4  = match(c, int32x4 , uint32x4);
    constexpr bool d_i32x8  = match(c, int32x8 , uint32x8);
    constexpr bool d_i32x16 = match(c, int32x16, uint32x16);
    constexpr bool d_i64x2  = match(c, int64x2 , uint64x2);
    constexpr bool d_i64x4  = match(c, int64x4 , uint64x4);
    constexpr bool d_i64x8  = match(c, int64x8 , uint64x8);

    // AVX512 note: yes, it's (v,p) and not (p,v), don't ask...
    // 64 bits integer data
    if      constexpr(i_32x8 && d_i64x8)          return _mm512_i32gather_epi64(v       , p, 8);
    else if constexpr(i_32x4 && d_i64x2)          return _mm_i32gather_epi64   (pl_t(p) , v, 8);
    else if constexpr(i_32x4 && d_i64x4)          return _mm256_i32gather_epi64(pl_t(p) , v, 8);
    else if constexpr(i_64x8 && d_i64x8)          return _mm512_i64gather_epi64(v       , p, 8);
    else if constexpr(i_64x4 && d_i64x4)          return _mm256_i64gather_epi64(pl_t(p) , v, 8);
    else if constexpr(i_64x2 && d_i64x2)          return _mm_i64gather_epi64   (pl_t(p) , v, 8);
    // 64 bits float data
    else if constexpr(i_32x8 && c == float64x8)   return _mm512_i32gather_pd(v, p, 8);
    else if constexpr(i_32x4 && c == float64x4)   return _mm256_i32gather_pd(p, v, 8);
    else if constexpr(i_32x4 && c == float64x2)   return _mm_i32gather_pd   (p, v, 8);
    else if constexpr(i_64x8 && c == float64x8)   return _mm512_i64gather_pd(v, p, 8);
    else if constexpr(i_64x4 && c == float64x4)   return _mm256_i64gather_pd(p, v, 8);
    else if constexpr(i_64x2 && c == float64x2)   return _mm_i64gather_pd   (p, v, 8);
    // 32 bits integer data
    else if constexpr(i_32x16 && d_i32x16)        return _mm512_i32gather_epi32(v,p,4);
    else if constexpr(i_32x8  && d_i32x8 )        return _mm256_i32gather_epi32(pi_t(p),v,4);
    else if constexpr(i_32x4  && d_i32x4 )        return _mm_i32gather_epi32   (pi_t(p),v,4);
    else if constexpr(i_64x8  && d_i32x8 )        return _mm512_i64gather_epi32(v,p,4);
    else if constexpr(i_64x4  && d_i32x4 )        return _mm256_i64gather_epi32(pi_t(p),v,4);
    else if constexpr(i_64x2  && d_i32x4 )        return _mm_i64gather_epi32   (pi_t(p),v,4);
    // 32 bits float data
    else if constexpr(i_32x16 && c == float32x16) return _mm512_i32gather_ps(v, p, 4);
    else if constexpr(i_32x8  && c == float32x8 ) return _mm256_i32gather_ps(p, v, 4);
    else if constexpr(i_32x4  && c == float32x4 ) return _mm_i32gather_ps   (p, v, 4);
    else if constexpr(i_64x8  && c == float32x8 ) return _mm512_i64gather_ps(v, p, 4);
    else if constexpr(i_64x4  && c == float32x4 ) return _mm256_i64gather_ps(p, v, 4);
    else if constexpr(i_64x2  && c == float32x4 ) return _mm_i64gather_ps   (p, v, 4);
    // Aggregation cases
    else if constexpr(has_aggregated_abi_v<wide<U, N>>)
    {
      auto[l,h] = v.slice();
      return wide<U,N>(gather(p,l),gather(p,h));
    }
    // All other cases
    else                                        return gather_(EVE_RETARGET(cpu_), p, v);
  }
}

template<typename U, conditional_expr C, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(avx2_), C cx, U const* p, wide<T, N> v) noexcept -> wide<U, N>
requires x86_abi<abi_t<T, N>>
{
  // Small index get converted then we recall gather
  if constexpr(sizeof(T) < 4)
  {
    return gather[cx](p, convert(v, as<std::int32_t>{}));
  }
  else
  {
    if constexpr( C::is_complete) return gather(p, v);
    else
    {
      using pl_t = long long const*;
      using pi_t = int const*;

      using enum category;
      constexpr auto i = categorize<wide<T, N>>();
      constexpr auto c = categorize<wide<U, N>>();

      constexpr bool i_32x4   = match(i, int32x4 , uint32x4);
      constexpr bool i_32x8   = match(i, int32x8 , uint32x8);
      constexpr bool i_32x16  = match(i, int32x16, uint32x16);
      constexpr bool i_64x2   = match(i, int64x2 , uint64x2);
      constexpr bool i_64x4   = match(i, int64x4 , uint64x4);
      constexpr bool i_64x8   = match(i, int64x8 , uint64x8);

      constexpr bool d_i32x4  = match(c, int32x4 , uint32x4);
      constexpr bool d_i32x8  = match(c, int32x8 , uint32x8);
      constexpr bool d_i32x16 = match(c, int32x16, uint32x16);
      constexpr bool d_i64x2  = match(c, int64x2 , uint64x2);
      constexpr bool d_i64x4  = match(c, int64x4 , uint64x4);
      constexpr bool d_i64x8  = match(c, int64x8 , uint64x8);

      auto src = alternative(cx, wide<U, N>{}, as<wide<U, N>> {});
      auto m   = [&]()
      {
        auto const mm = expand_mask(cx, as<wide<U, N>> {});

        // Extract the kmask from the logical
        if constexpr(current_api >= avx512) return mm.storage().value;
        // On AVX512, there is no AVX2-like mask, so we convert the kmask back to a wide mask
        // On AVX2, this is no-op
        else                                return mm.mask();
      }();

      // 64 bits integer data
      if      constexpr(i_32x8 && d_i64x8)  return _mm512_mask_i32gather_epi64(src,m, v     ,p,8);
      else if constexpr(i_32x4 && d_i64x2)  return _mm_mask_i32gather_epi64   (src,pl_t(p),v,m,8);
      else if constexpr(i_32x4 && d_i64x4)  return _mm256_mask_i32gather_epi64(src,pl_t(p),v,m,8);
      else if constexpr(i_64x8 && d_i64x8)  return _mm512_mask_i64gather_epi64(src,m, v     ,p,8);
      else if constexpr(i_64x4 && d_i64x4)  return _mm256_mask_i64gather_epi64(src,pl_t(p),v,m,8);
      else if constexpr(i_64x2 && d_i64x2)  return _mm_mask_i64gather_epi64   (src,pl_t(p),v,m,8);
      // 64 bits float data
      else if constexpr(i_32x8 && c == float64x8) return _mm512_mask_i32gather_pd(src,m,v,p,8);
      else if constexpr(i_32x4 && c == float64x4) return _mm256_mask_i32gather_pd(src,p,v,m,8);
      else if constexpr(i_32x4 && c == float64x2) return _mm_mask_i32gather_pd   (src,p,v,m,8);
      else if constexpr(i_64x8 && c == float64x8) return _mm512_mask_i64gather_pd(src,m,v,p,8);
      else if constexpr(i_64x4 && c == float64x4) return _mm256_mask_i64gather_pd(src,p,v,m,8);
      else if constexpr(i_64x2 && c == float64x2) return _mm_mask_i64gather_pd   (src,p,v,m,8);
      // 32 bits integer data
      else if constexpr(i_32x16 && d_i32x16)  return _mm512_mask_i32gather_epi32(src,m,v,p,4);
      else if constexpr(i_32x8  && d_i32x8 )  return _mm256_mask_i32gather_epi32(src,pi_t(p),v,m,4);
      else if constexpr(i_32x4  && d_i32x4 )  return _mm_mask_i32gather_epi32   (src,pi_t(p),v,m,4);
      else if constexpr(i_64x8  && d_i32x8 )  return _mm512_mask_i64gather_epi32(src,m,v,p,4);
      else if constexpr(i_64x4  && d_i32x4 )  return _mm256_mask_i64gather_epi32(src,pi_t(p),v,m,4);
      else if constexpr(i_64x2  && d_i32x4 )  return _mm_mask_i64gather_epi32   (src,pi_t(p),v,m,4);
      // 32 bits float data
      else if constexpr(i_32x16 && c == float32x16) return _mm512_mask_i32gather_ps(src,m,v,p,4);
      else if constexpr(i_32x8  && c == float32x8 ) return _mm256_mask_i32gather_ps(src,p,v,m,4);
      else if constexpr(i_32x4  && c == float32x4 ) return _mm_mask_i32gather_ps   (src,p,v,m,4);
      else if constexpr(i_64x8  && c == float32x8 ) return _mm512_mask_i64gather_ps(src,m,v,p,4);
      else if constexpr(i_64x4  && c == float32x4 ) return _mm256_mask_i64gather_ps(src,p,v,m,4);
      else if constexpr(i_64x2  && c == float32x4 ) return _mm_mask_i64gather_ps   (src,p,v,m,4);
      // All other cases
      else                                          return gather_(EVE_RETARGET(cpu_), p, v);
    }
  }
}
}
