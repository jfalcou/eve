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
    constexpr auto et_size = sizeof(T) * G;
    constexpr auto n  = N() / G;

    if constexpr (n == 2 && et_size == 8)
    {
      if constexpr ( et_size == 8 && std::floating_point<T> )
      {
        using doubles  = typename wide<T, N>::template rebind<double,  eve::fixed<2>>;

        auto cast_v0 = eve::bit_cast(v0, eve::as<doubles>{});
        auto cast_v1 = eve::bit_cast(v1, eve::as<doubles>{});
        doubles res_l = _mm_unpacklo_pd(cast_v0, cast_v1);
        doubles res_h = _mm_unpackhi_pd(cast_v0, cast_v1);

        return {eve::bit_cast(res_l, eve::as(v0)), eve::bit_cast(res_h, eve::as(v0))};
      }
      else if constexpr ( et_size == 8 )
      {
        wide<T, N> res_l = _mm_unpacklo_epi64(v0, v1);
        wide<T, N> res_h = _mm_unpackhi_epi64(v0, v1);

        return eve::combine(res_l, res_h);
      }
    }
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
  }
}
