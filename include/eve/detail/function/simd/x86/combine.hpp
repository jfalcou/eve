//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/function/simd/x86/make.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 2*128-bits regular combine
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
  // 256-bits combine
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(avx_ const &, wide<T, N, avx_> const &l, wide<T, N, avx_> const &h) noexcept
  {
    using that_t = typename wide<T, typename N::combined_type>::storage_type;
    return that_t{l, h};
  }

  // -----------------------------------------------------------------------------------------------
  // 2*128-bits to 256-bits combine
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(avx_ const &, wide<T, N, sse_> const &l, wide<T, N, sse_> const &h) noexcept
  {
    if constexpr(N::value * sizeof(T) == limits<eve::sse2_>::bytes)
    {
      if constexpr(std::is_same_v<T, double>)
        return _mm256_insertf128_pd(_mm256_castpd128_pd256(l), h, 1);

      if constexpr(std::is_same_v<T, float>)
        return _mm256_insertf128_ps(_mm256_castps128_ps256(l), h, 1);

      if constexpr(std::is_integral_v<T>)
        return _mm256_insertf128_si256(_mm256_castsi128_si256(l), h, 1);
    }
    else
    {
      return combine(sse2_{}, l, h);
    }
  }
}

#endif
