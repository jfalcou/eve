//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/function/simd/x86/sse2/make.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE typename wide<T, typename N::combined_type>::storage_type
  combine(sse2_ const &, wide<T, N, sse_> const &l, wide<T, N, sse_> const &h) noexcept
  {
    using t_t = wide<T, typename N::combined_type>;
    using s_t = typename t_t::storage_type;

    // If we aggregate two fully sized wide, just coalesce inside new storage
    if constexpr(N::value * sizeof(T) == limits<eve::sse2_>::bytes) return s_t{l, h};

    // Handle half-storage
    if constexpr(2 * N::value * sizeof(T) == limits<eve::sse2_>::bytes)
    {
      if constexpr(std::is_same_v<T, double>) return _mm_shuffle_pd(l, h, 0);
      if constexpr(std::is_same_v<T, float>) return _mm_shuffle_ps(l, h, 0x44);
      if constexpr(std::is_integral_v<T>)
        return _mm_castps_si128(
            _mm_shuffle_ps(_mm_castsi128_ps(l.storage()), _mm_castsi128_ps(h.storage()), 0x44));
    }

    // Handle quarter-storage
    if constexpr(4 * N::value * sizeof(T) == limits<eve::sse2_>::bytes)
    {
      if constexpr(std::is_same_v<T, float>)
      {
        t_t that  = l.storage();
        that[ 1 ] = h[ 0 ];
        return that.storage();
      }

      if constexpr(std::is_integral_v<T>)
        return _mm_shuffle_epi32(
            _mm_castps_si128(
                _mm_shuffle_ps(_mm_castsi128_ps(l.storage()), _mm_castsi128_ps(h.storage()), 0x44)),
            0x88);
    }

    // Handle 1/8th and 1/16th -storage - Those cases are obviously integrals
    if constexpr(std::is_integral_v<T> && ((sizeof(T) != 8) && (N::value == 2)))
      return make(as_<T>{}, eve::sse_{}, l[ 0 ], l[ 1 ], h[ 0 ], h[ 1 ]);

    if constexpr(std::is_integral_v<T> && (sizeof(T) != 8) && (N::value == 1))
      return make(as_<T>{}, eve::sse_{}, l[ 0 ], h[ 0 ]);
  }

  // -----------------------------------------------------------------------------------------------
  // logicals
  template<typename T, typename N>
  EVE_FORCEINLINE typename wide<logical<T>, typename N::combined_type>::storage_type
  combine(sse2_ const &,
          wide<logical<T>, N, sse_> const &l,
          wide<logical<T>, N, sse_> const &h) noexcept
  {
    using that_t = wide<logical<T>, typename N::combined_type>;

    if constexpr(N::value * sizeof(T) == limits<eve::sse2_>::bytes)
      return typename that_t::storage_type{l, h};
    else
      return combine(sse2_{}, wide<T, N, sse_>(l.storage()), wide<T, N, sse_>(h.storage()));
  }
}

#endif
