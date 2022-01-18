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
  template <typename T, typename N>
  EVE_FORCEINLINE wide<T, N> deinterleave_shuffle_(EVE_SUPPORTS(sse2_), wide<T, N> v) noexcept
    requires ( N() > 2 ) && x86_abi<abi_t<T, N>>
  {
    // constexpr auto c = categorize<wide<T, N>>();

    if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && sizeof(T) == 64 )
    {
      auto [l, h] = v.slice();
      return eve::deinterleave_shuffle(l, h);
    }
    else return deinterleave_shuffle_(EVE_RETARGET(cpu_), v);
  }

  template <typename T, typename N>
  EVE_FORCEINLINE wide<T, typename N::combined_type>
  deinterleave_shuffle_(EVE_SUPPORTS(sse2_), wide<T, N> v0, wide<T, N> v1) noexcept
    requires ( N()() > 1 ) && x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    using w_t = wide<T, N>;

         if constexpr ( c == category::float64x2                       ) return {w_t{_mm_unpacklo_pd   (v0, v1)}, w_t{_mm_unpackhi_pd   (v0, v1)}};
    else if constexpr ( match(c,category::int64x2, category::uint64x2) ) return {w_t{_mm_unpacklo_epi64(v0, v1)}, w_t{_mm_unpackhi_epi64(v0, v1)}};
    else if constexpr ( c == category::float32x4 && N() == 2           ) return _mm_unpacklo_ps(v0, v1);
    else if constexpr ( c == category::float32x4                       )
    {
      auto half_done_0  = eve::bit_cast(eve::deinterleave_shuffle(v0), eve::as<wide<double, typename N::split_type>>{});
      auto half_done_1  = eve::bit_cast(eve::deinterleave_shuffle(v1), eve::as<wide<double, typename N::split_type>>{});
      auto done = eve::deinterleave_shuffle(half_done_0, half_done_1);

      return eve::bit_cast(done, eve::as<wide<T, typename N::combined_type>>{});

    }
    else return deinterleave_shuffle_(EVE_RETARGET(cpu_), v0, v1);
  }
}
