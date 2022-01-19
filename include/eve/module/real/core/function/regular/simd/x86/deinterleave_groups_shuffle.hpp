//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  auto deinterleave_groups_shuffle_(EVE_SUPPORTS(sse2_), wide<T, N> v, fixed<G>)
    requires (G * 2 < N()) && x86_abi<abi_t<T, N>>
  {
    return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v, eve::lane<G>);
  }

  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  wide<T, typename N::combined_type>
  deinterleave_groups_shuffle_(EVE_SUPPORTS(sse2_), wide<T, N> v0, wide<T, N> v1, fixed<G>)
    requires (G < N()) && x86_abi<abi_t<T, N>>
  {
    constexpr auto g_sz = sizeof(T) * G;
    constexpr auto n  = N() / G;
    using w_t = wide<T, N>;

    // Doing 2 is the most important case since we can deinterleave with G = N() / 2 and then deinterleave each half.
    // This deinterleaving halves is done in 2 instructions.
    // So - 2 for this shuffle + shuffle each.
    // After looking through the intrinsics set, I couldn't find anything that'd do at least 4 groups from each (8 total) before avx512

    if constexpr ( current_api == avx512 && n == 4 )
    {
      if constexpr ( g_sz == 16 && !std::floating_point<T> ) return {w_t{_mm512_shuffle_i32x4(v0, v1, 0x88)}, w_t{_mm512_shuffle_i32x4(v0, v1, 0xdd)}};
      else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
    }
    else if constexpr ( n == 2 )
    {
      // 16 bytes
           if constexpr ( g_sz == 1                           ) return _mm_unpacklo_epi8 (v0, v1);
      else if constexpr ( g_sz == 2                           ) return _mm_unpacklo_epi16(v0, v1);
      else if constexpr ( g_sz == 4 && std::floating_point<T> ) return _mm_unpacklo_ps   (v0, v1);
      else if constexpr ( g_sz == 4                           ) return _mm_unpacklo_epi32(v0, v1);
      else if constexpr ( g_sz == 8 && std::floating_point<T> )
      {
        using doubles  = typename wide<T, N>::template rebind<double,  eve::fixed<2>>;

        auto cast_v0 = eve::bit_cast(v0, eve::as<doubles>{});
        auto cast_v1 = eve::bit_cast(v1, eve::as<doubles>{});
        doubles res_l = _mm_unpacklo_pd(cast_v0, cast_v1);
        doubles res_h = _mm_unpackhi_pd(cast_v0, cast_v1);

        return {eve::bit_cast(res_l, eve::as(v0)), eve::bit_cast(res_h, eve::as(v0))};
      }
      else if constexpr ( g_sz == 8                             ) return {w_t{_mm_unpacklo_epi64(v0, v1)}, w_t{_mm_unpackhi_epi64(v0, v1)}};
      // avx at least
      else if constexpr ( g_sz == 16 && std::same_as<T, double> ) return {w_t{_mm256_permute2f128_pd   (v0, v1, 0x20)}, w_t{_mm256_permute2f128_pd   (v0, v1, 0x31)}};
      else if constexpr ( g_sz == 16 && std::same_as<T, float>  ) return {w_t{_mm256_permute2f128_ps   (v0, v1, 0x20)}, w_t{_mm256_permute2f128_ps   (v0, v1, 0x31)}};
      else if constexpr ( g_sz == 16                            ) return {w_t{_mm256_permute2f128_si256(v0, v1, 0x20)}, w_t{_mm256_permute2f128_si256(v0, v1, 0x31)}};
      // avx512 at least
      else if constexpr ( g_sz == 32 && std::same_as<T, double> ) return {w_t{_mm512_shuffle_f64x2(v0, v1, 0x44)}, w_t{_mm512_shuffle_f64x2(v0, v1, 0xee)}};
      else if constexpr ( g_sz == 32 && std::same_as<T, float>  ) return {w_t{_mm512_shuffle_f32x4(v0, v1, 0x44)}, w_t{_mm512_shuffle_f32x4(v0, v1, 0xee)}};
      else if constexpr ( g_sz == 32                            ) return {w_t{_mm512_shuffle_i32x4(v0, v1, 0x44)}, w_t{_mm512_shuffle_i32x4(v0, v1, 0xee)}};
    }
    // Will aggregate for less than native or deinterleave each and then come back here
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
  }
}
