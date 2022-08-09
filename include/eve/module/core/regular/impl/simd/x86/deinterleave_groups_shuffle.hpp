//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/swap_adjacent_groups.hpp>

namespace eve::detail
{
template<typename T, typename N, std::ptrdiff_t G>
    EVE_FORCEINLINE wide<T, N>
    deinterleave_groups_shuffle_(EVE_SUPPORTS(sse2_), wide<T, N> v, fixed<G>) requires(N() / G > 2)
    && x86_abi<abi_t<T, N>>
{
  constexpr auto g_sz = sizeof(T) * G;
  constexpr auto n    = N() / G;

  // we start with 4, 2 groups is a no op
  if constexpr( n == 4 )
  {
    // g_sz 16
    // I can only do in 2 heavy instructions, or rely on a mask in a register.
    // I picked register - that's done by the basic shuffle.

    // g_sz 8
    // on avx2 there is a perfect shuffle
    if constexpr( current_api == avx && g_sz == 8 )
    {
      // only double shuffle is avaliable
      if constexpr( !std::same_as<double, T> )
        return deinterleave_groups_shuffle_as_doubles(v, lane<G>);
      else
      {
        auto swapped = swap_adjacent_groups(v, lane<G * 2>);

        auto lo = _mm256_unpacklo_pd(v, swapped);
        auto hi = _mm256_unpackhi_pd(swapped, v);
        return _mm256_permute2f128_pd(lo, hi, 0x30);
      }
    }
    // g_sz 2 and 4 have a perfect shuffle
    else if constexpr( g_sz == 1 )
    {
      auto duplicate = _mm_shufflelo_epi16(v, _MM_SHUFFLE(3, 2, 1, 1));
      return _mm_unpacklo_epi8(v, duplicate);
    }
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v, eve::lane<G>);
  }
  else if constexpr( n == 8 )
  {
    // g_sz 8 - if we couldn't do 16x4 - no chance
    // g_sz 4 - 1 light 1 heavy on avx2 instruction as oppose to having to occupy a register
    //          on avx, splitting will be not ideal as well
    if constexpr( g_sz == 4 )
    {
      auto floats = eve::bit_cast(v, eve::as<wide<float, fixed<n>>> {});
      floats      = _mm256_permute_ps(floats, _MM_SHUFFLE(3, 1, 2, 0));
      v           = eve::bit_cast(floats, as(v));
      return deinterleave_groups_shuffle(v, lane<N() / 4>);
    }
    // pshuvb is crazy cheap, let's use the register when >= ssse3
    // otherwise - same idea as with floats
    else if constexpr( g_sz == 2 && current_api < ssse3 )
    {
      v = _mm_shufflelo_epi16(v, _MM_SHUFFLE(3, 1, 2, 0));
      v = _mm_shufflehi_epi16(v, _MM_SHUFFLE(3, 1, 2, 0));
      return _mm_shuffle_epi32(v, _MM_SHUFFLE(3, 1, 2, 0));
    }
    // should use pshuvb for chars when it's avaliable
    // otherwise we have to use shorts, no chars shuffles
    else if constexpr( g_sz == 1 && current_api < ssse3 )
    {
      auto shorts = eve::convert(v, eve::as<std::uint16_t> {});
      shorts      = deinterleave_groups_shuffle(shorts, lane<G>);
      return eve::convert(shorts, as<T> {});
    }
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v, eve::lane<G>);
  }
  else if constexpr( n == 16 )
  {
    // g_sz 4 - basic will do
    // g_sz 2 - on avx512 there is a permute
    // avx2 - pshuvb each halve and deinterleave
    if constexpr( g_sz == 2 && current_api == avx2 )
    {
      auto half_pattern =
          as_indexes<wide<std::uint8_t, fixed<n>>>(deinterleave_groups_shuffle_pattern<g_sz, 16>);
      v = _mm256_shuffle_epi8(v, eve::combine(half_pattern, half_pattern));
      return deinterleave_groups_shuffle(v, lane<N() / 4>);
    }
    // avx - slice and deinterleave
    else if constexpr( g_sz == 2 )
    {
      auto [lo, hi] = v.slice();
      lo            = deinterleave_groups_shuffle(lo, lane<G>);
      hi            = deinterleave_groups_shuffle(hi, lane<G>);
      return deinterleave_groups_shuffle(lo, hi, lane<N() / 4>);
    }
    // pshuvb
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v, eve::lane<G>);
  }
  else if constexpr( g_sz == 2 && current_api == avx512 )
  {
    // has a permute
    return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v, eve::lane<G>);
  }
  else if constexpr( (n == 32 || n == 64) && g_sz == 1 )
  {
    if constexpr( current_api == avx )
    {
      auto [lo, hi] = v.slice();

      lo = deinterleave_groups_shuffle(lo, lane<G>);
      hi = deinterleave_groups_shuffle(hi, lane<G>);

      return deinterleave_groups_shuffle(lo, hi, lane<N() / 4>);
    }
    else
    {
      // pshuvb it is
      using byte_idxs         = typename wide<T, N>::template rebind<std::uint8_t, fixed<16>>;
      byte_idxs pattern       = as_indexes<byte_idxs>(deinterleave_groups_shuffle_pattern<1, 16>);
      auto      pattern_twice = eve::combine(pattern, pattern);

      if constexpr( n == 32 ) v = _mm256_shuffle_epi8(v, pattern_twice);
      else v = _mm512_shuffle_epi8(v, eve::combine(pattern_twice, pattern_twice));

      return deinterleave_groups_shuffle(v, lane<8>);
    }
  }
}

template<typename T, typename N, std::ptrdiff_t G>
    EVE_FORCEINLINE wide<T, typename N::combined_type>
                    deinterleave_groups_shuffle_(EVE_SUPPORTS(sse2_),
                                                 wide<T, N> v0,
                                                 wide<T, N> v1,
                                                 fixed<G>) requires(G < N())
    && x86_abi<abi_t<T, N>>
{
  constexpr auto g_sz = sizeof(T) * G;
  constexpr auto n    = N() / G;
  using w_t           = wide<T, N>;

  // Doing 2 is the most important case since we can deinterleave with G = N() / 2 and then
  // deinterleave each half. This deinterleaving halves is done in 2 instructions (I mean g_sz * n
  // >= 16, less than native reg will aggrgate) So - 2 for this shuffle + shuffle each.
  if constexpr( n == 2 )
  {
    // 16 bytes
    if constexpr( g_sz == 1 ) return _mm_unpacklo_epi8(v0, v1);
    else if constexpr( g_sz == 2 ) return _mm_unpacklo_epi16(v0, v1);
    else if constexpr( g_sz == 4 && std::floating_point<T> ) return _mm_unpacklo_ps(v0, v1);
    else if constexpr( g_sz == 4 ) return _mm_unpacklo_epi32(v0, v1);
    else if constexpr( g_sz == 8 && std::same_as<float, T> )
      return deinterleave_groups_shuffle_as_doubles(v0, v1, lane<G>);
    else if constexpr( g_sz == 8 && std::same_as<double, T> )
      return {w_t {_mm_unpacklo_pd(v0, v1)}, w_t {_mm_unpackhi_pd(v0, v1)}};
    else if constexpr( g_sz == 8 )
      return {w_t {_mm_unpacklo_epi64(v0, v1)}, w_t {_mm_unpackhi_epi64(v0, v1)}};
    // avx at least
    else if constexpr( g_sz == 16 && std::same_as<T, double> )
      return {w_t {_mm256_permute2f128_pd(v0, v1, 0x20)},
              w_t {_mm256_permute2f128_pd(v0, v1, 0x31)}};
    else if constexpr( g_sz == 16 && std::same_as<T, float> )
      return {w_t {_mm256_permute2f128_ps(v0, v1, 0x20)},
              w_t {_mm256_permute2f128_ps(v0, v1, 0x31)}};
    else if constexpr( g_sz == 16 )
      return {w_t {_mm256_permute2f128_si256(v0, v1, 0x20)},
              w_t {_mm256_permute2f128_si256(v0, v1, 0x31)}};
    // avx512 at least
    else if constexpr( g_sz == 32 && std::same_as<T, double> )
      return {w_t {_mm512_shuffle_f64x2(v0, v1, 0x44)}, w_t {_mm512_shuffle_f64x2(v0, v1, 0xee)}};
    else if constexpr( g_sz == 32 && std::same_as<T, float> )
      return {w_t {_mm512_shuffle_f32x4(v0, v1, 0x44)}, w_t {_mm512_shuffle_f32x4(v0, v1, 0xee)}};
    else if constexpr( g_sz == 32 )
      return {w_t {_mm512_shuffle_i32x4(v0, v1, 0x44)}, w_t {_mm512_shuffle_i32x4(v0, v1, 0xee)}};
  }
  // After looking through the intrinsics set, I couldn't find anything that'd do at least 4 groups
  // before avx512
  else if constexpr( current_api == avx512 && g_sz == 16 )
  {
    static_assert(n == 4);
    if constexpr( std::same_as<T, float> )
      return {w_t {_mm512_shuffle_f32x4(v0, v1, 0x88)}, w_t {_mm512_shuffle_f32x4(v0, v1, 0xdd)}};
    else if constexpr( std::same_as<T, double> )
      return {w_t {_mm512_shuffle_f64x2(v0, v1, 0x88)}, w_t {_mm512_shuffle_f64x2(v0, v1, 0xdd)}};
    else
      return {w_t {_mm512_shuffle_i32x4(v0, v1, 0x88)}, w_t {_mm512_shuffle_i32x4(v0, v1, 0xdd)}};
  }
  // less than full 16 bytes, only g_sz 2 fits.
  else if constexpr( current_api == avx512 && g_sz >= 2 && g_sz * n < 16 )
  {
    static_assert(g_sz == 2);

    using idx_t = wide<make_integer_t<g_sz, unsigned>, eve::fixed<n * 2>>;
    idx_t idx {[](int i, int size)
               {
                 if( i < size / 4 ) return i * 2;
                 if( i < size / 2 ) return i * 2 + size / 2;
                 i -= size / 2;
                 if( i < size / 4 ) return i * 2 + 1;
                 else return i * 2 + 1 + size / 2;
               }};

    return _mm_permutex2var_epi16(v0, idx, v1);
  }
  else if constexpr( current_api == avx512 && g_sz >= 2 )
  {
    using idx_t = wide<make_integer_t<g_sz, unsigned>, eve::fixed<n>>;
    idx_t lo_idx {[](int i, int) { return i * 2; }};
    idx_t hi_idx {[](int i, int) { return i * 2 + 1; }};

    // These should probably be in basic shuffle for 2 registers when we have one.
    if constexpr( g_sz * n == 16 && g_sz == 2 )
      return {w_t {_mm_permutex2var_epi16(v0, lo_idx, v1)},
              w_t {_mm_permutex2var_epi16(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 32 && g_sz == 2 )
      return {w_t {_mm256_permutex2var_epi16(v0, lo_idx, v1)},
              w_t {_mm256_permutex2var_epi16(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 64 && g_sz == 2 )
      return {w_t {_mm512_permutex2var_epi16(v0, lo_idx, v1)},
              w_t {_mm512_permutex2var_epi16(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 16 && g_sz == 4 && std::same_as<float, T> )
      return {w_t {_mm_permutex2var_ps(v0, lo_idx, v1)}, w_t {_mm_permutex2var_ps(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 32 && g_sz == 4 && std::same_as<float, T> )
      return {w_t {_mm256_permutex2var_ps(v0, lo_idx, v1)},
              w_t {_mm256_permutex2var_ps(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 64 && g_sz == 4 && std::same_as<float, T> )
      return {w_t {_mm512_permutex2var_ps(v0, lo_idx, v1)},
              w_t {_mm512_permutex2var_ps(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 16 && g_sz == 4 )
      return {w_t {_mm_permutex2var_epi32(v0, lo_idx, v1)},
              w_t {_mm_permutex2var_epi32(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 32 && g_sz == 4 )
      return {w_t {_mm256_permutex2var_epi32(v0, lo_idx, v1)},
              w_t {_mm256_permutex2var_epi32(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 64 && g_sz == 4 )
      return {w_t {_mm512_permutex2var_epi32(v0, lo_idx, v1)},
              w_t {_mm512_permutex2var_epi32(v0, hi_idx, v1)}};
    // From this point better use doubles shuffle floats to avoid duplicating constants
    else if constexpr( std::same_as<float, T> )
      return deinterleave_groups_shuffle_as_doubles(v0, v1, lane<G>);
    else if constexpr( g_sz * n == 16 && g_sz == 8 && std::same_as<double, T> )
      return {w_t {_mm_permutex2var_pd(v0, lo_idx, v1)}, w_t {_mm_permutex2var_pd(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 32 && g_sz == 8 && std::same_as<double, T> )
      return {w_t {_mm256_permutex2var_pd(v0, lo_idx, v1)},
              w_t {_mm256_permutex2var_pd(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 64 && g_sz == 8 && std::same_as<double, T> )
      return {w_t {_mm512_permutex2var_pd(v0, lo_idx, v1)},
              w_t {_mm512_permutex2var_pd(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 16 && g_sz == 8 )
      return {w_t {_mm_permutex2var_epi64(v0, lo_idx, v1)},
              w_t {_mm_permutex2var_pd(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 32 && g_sz == 8 )
      return {w_t {_mm256_permutex2var_epi64(v0, lo_idx, v1)},
              w_t {_mm256_permutex2var_epi64(v0, hi_idx, v1)}};
    else if constexpr( g_sz * n == 64 && g_sz == 8 )
      return {w_t {_mm512_permutex2var_epi64(v0, lo_idx, v1)},
              w_t {_mm512_permutex2var_epi64(v0, hi_idx, v1)}};
  }
  // Will aggregate for less than native or deinterleave each and then come back here
  else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
}
}
