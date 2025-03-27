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
  template<callable_options O, typename U, integral_scalar_value T, typename N>
  EVE_FORCEINLINE wide<U, N> gather_(EVE_REQUIRES(avx2_), O const& opts, U const* p, wide<T, N> v) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    const auto cx = opts[condition_key];

    using out_t = wide<U, N>;
    constexpr auto i = categorize<wide<T, N>>();
    constexpr auto c = categorize<out_t>();

    constexpr bool i_32x4   = match(i, category::int32x4, category::uint32x4);
    constexpr bool i_32x8   = match(i, category::int32x8, category::uint32x8);
    constexpr bool i_64x2   = match(i, category::int64x2, category::uint64x2);
    constexpr bool i_64x4   = match(i, category::int64x4, category::uint64x4);

    constexpr bool d_i32x4  = match(c, category::int32x4, category::uint32x4);
    constexpr bool d_i32x8  = match(c, category::int32x8, category::uint32x8);
    constexpr bool d_i64x2  = match(c, category::int64x2, category::uint64x2);
    constexpr bool d_i64x4  = match(c, category::int64x4, category::uint64x4);

    // Ignore All case : just return the alternative if any
    if      constexpr(C::is_complete && !C::is_inverted)  return alternative(cx, out_t{}, as<out_t>{});
    // Aggregation cases
    else if constexpr(has_aggregated_abi_v<out_t>)        return gather[cx].retarget(cpu_{}, p, v);
    // Smaller data goes through the generic cases
    else if constexpr(sizeof(U) <= 2)                     return gather[cx].retarget(cpu_{}, p, v);
    // Small index get converted then we recall gather
    else if constexpr(sizeof(T) <  4)                     return gather[cx](p, convert(v, as<std::int32_t>{}));
    else if constexpr (current_api >= avx512)
    {
      constexpr bool i_32x16  = match(i, category::int32x16, category::uint32x16);
      constexpr bool i_64x8   = match(i, category::int64x8 , category::uint64x8);
      constexpr bool d_i32x16 = match(c, category::int32x16, category::uint32x16);
      constexpr bool d_i64x8  = match(c, category::int64x8 , category::uint64x8);

      const bool masked = !C::is_complete; // ingore_none

      auto s = alternative(cx, out_t{}, as<out_t> {});
      auto m = expand_mask(cx, as<out_t> {}).storage().value;

      if      constexpr(i_32x8  && d_i64x8)
      {
        if constexpr (masked)                                 return _mm512_mask_i32gather_epi64 (s, m, v, p, 8);
        else                                                  return _mm512_i32gather_epi64      (v, p, 8);
      }
      else if constexpr(i_32x4  && d_i64x2                  ) return _mm_mmask_i32gather_epi64   (s, m, v, p, 8);
      else if constexpr(i_32x4  && d_i64x4                  ) return _mm256_mmask_i32gather_epi64(s, m, v, p, 8);
      else if constexpr(i_64x8  && d_i64x8                  )
      {
        if constexpr (masked)                                 return _mm512_mask_i64gather_epi64 (s, m, v, p, 8);
        else                                                  return _mm512_i64gather_epi64      (v, p, 8);
      }
      else if constexpr(i_64x4  && d_i64x4                  ) return _mm256_mmask_i64gather_epi64(s, m, v, p, 8);
      else if constexpr(i_64x2  && d_i64x2                  ) return _mm_mmask_i64gather_epi64   (s, m, v, p, 8);
      else if constexpr(i_32x16 && d_i32x16                 )
      {
        if constexpr (masked)                                 return _mm512_mask_i32gather_epi32 (s, m, v, p, 4);
        else                                                  return _mm512_i32gather_epi32      (v, p, 4);
      }
      else if constexpr(i_32x8  && d_i32x8                  ) return _mm256_mmask_i32gather_epi32(s, m, v, p, 4);
      else if constexpr(i_32x4  && d_i32x4                  ) return _mm_mmask_i32gather_epi32   (s, m, v, p, 4);
      else if constexpr(i_64x8  && d_i32x8                  )
      {
        if constexpr (masked)                                 return _mm512_mask_i64gather_epi32 (s, m, v, p, 4);
        else                                                  return _mm512_i64gather_epi32      (v, p, 4);
      }
      else if constexpr(i_64x4  && d_i32x4                  ) return _mm256_mmask_i64gather_epi32(s, m, v, p, 4);
      else if constexpr(i_64x2  && d_i32x4                  ) return _mm_mmask_i64gather_epi32   (s, m, v, p, 4);
      else if constexpr(i_32x8  && c == category::float64x8 )
      {
        if constexpr (masked)                                 return _mm512_mask_i32gather_pd    (s, m, v, p, 8);
        else                                                  return _mm512_i32gather_pd         (v, p, 8);
      }
      else if constexpr(i_32x4  && c == category::float64x4 ) return _mm256_mmask_i32gather_pd   (s, m, v, p, 8);
      else if constexpr(i_32x4  && c == category::float64x2 ) return _mm_mmask_i32gather_pd      (s, m, v, p, 8);
      else if constexpr(i_64x8  && c == category::float64x8 )
      {
        if constexpr (masked)                                 return _mm512_mask_i64gather_pd    (s, m, v, p, 8);
        else                                                  return _mm512_i64gather_pd         (v, p, 8);
      }
      else if constexpr(i_64x4  && c == category::float64x4 ) return _mm256_mmask_i64gather_pd   (s, m, v, p, 8);
      else if constexpr(i_64x2  && c == category::float64x2 ) return _mm_mmask_i64gather_pd      (s, m, v, p, 8);
      else if constexpr(i_32x16 && c == category::float32x16)
      {
        if constexpr (masked)                                 return _mm512_mask_i32gather_ps    (s, m, v, p, 4);
        else                                                  return _mm512_i32gather_ps         (v, p, 4);
      }
      else if constexpr(i_32x8  && c == category::float32x8 ) return _mm256_mmask_i32gather_ps   (s, m, v, p, 4);
      else if constexpr(i_32x4  && c == category::float32x4 ) return _mm_mmask_i32gather_ps      (s, m, v, p, 4);
      else if constexpr(i_64x8  && c == category::float32x8 )
      {
        if constexpr (masked)                                 return _mm512_mask_i64gather_ps    (s, m, v, p, 4);
        else                                                  return _mm512_i64gather_ps         (v, p, 4);
      }
      else if constexpr(i_64x4  && c == category::float32x4 ) return _mm256_mmask_i64gather_ps   (s, m, v, p, 4);
      else if constexpr(i_64x2  && c == category::float32x4 ) return _mm_mmask_i64gather_ps      (s, m, v, p, 4);
    }
    else
    {
      using pl_t = long long const*;
      using pi_t = int const*;
      auto s = alternative(cx, out_t{}, as<out_t> {});
      auto m = expand_mask(cx, as<out_t> {});

      if      constexpr (i_32x4 && d_i64x2                 ) return _mm_mask_i32gather_epi64   (s,pl_t(p),v,m,8);
      else if constexpr (i_64x2 && d_i64x2                 ) return _mm_mask_i64gather_epi64   (s,pl_t(p),v,m,8);
      else if constexpr (i_32x4 && d_i64x4                 ) return _mm256_mask_i32gather_epi64(s,pl_t(p),v,m,8);
      else if constexpr (i_64x4 && d_i64x4                 ) return _mm256_mask_i64gather_epi64(s,pl_t(p),v,m,8);
      else if constexpr (i_32x4 && d_i32x4                 ) return _mm_mask_i32gather_epi32   (s,pi_t(p),v,m,4);
      else if constexpr (i_64x2 && d_i32x4                 ) return _mm_mask_i64gather_epi32   (s,pi_t(p),v,m,4);
      else if constexpr (i_32x8 && d_i32x8                 ) return _mm256_mask_i32gather_epi32(s,pi_t(p),v,m,4);
      else if constexpr (i_64x4 && d_i32x4                 ) return _mm256_mask_i64gather_epi32(s,pi_t(p),v,m,4);
      else if constexpr (i_32x4 && c == category::float64x2) return _mm_mask_i32gather_pd      (s,p,v,m,8);
      else if constexpr (i_64x2 && c == category::float64x2) return _mm_mask_i64gather_pd      (s,p,v,m,8);
      else if constexpr (i_32x4 && c == category::float64x4) return _mm256_mask_i32gather_pd   (s,p,v,m,8);
      else if constexpr (i_64x4 && c == category::float64x4) return _mm256_mask_i64gather_pd   (s,p,v,m,8);
      else if constexpr (i_32x4 && c == category::float32x4) return _mm_mask_i32gather_ps      (s,p,v,m,4);
      else if constexpr (i_64x2 && c == category::float32x4) return _mm_mask_i64gather_ps      (s,p,v,m,4);
      else if constexpr (i_32x8 && c == category::float32x8) return _mm256_mask_i32gather_ps   (s,p,v,m,4);
      else if constexpr (i_64x4 && c == category::float32x4) return _mm256_mask_i64gather_ps   (s,p,v,m,4);
    }
  }
}
