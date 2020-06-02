//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename I, typename N, auto V>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(sse2_),
                             wide<T, N, sse_> const &v0,
                             std::integral_constant<I, V> const &) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr( spy::architecture == spy::amd64_ )
      {
        if constexpr(std::is_same_v<T, float>)
        {
          return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v0), 4 * V)));
        }
        else // if  constexpr(std::is_same_v<T, double)
        {
          return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v0), 8 * V)));
        }
      }
      else
      {
        return v0[ V ];
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) == 2)
      {
        return static_cast<T>(_mm_extract_epi16(v0, V));
      }
      else if constexpr(current_api > sse4_1)
      {
        if constexpr(sizeof(T) == 1)
        {
          return static_cast<T>(_mm_extract_epi8(v0, V));
        }
        else if constexpr(sizeof(T) == 4)
        {
          return static_cast<T>(_mm_extract_epi32(v0, V));
        }
        else if constexpr(sizeof(T) == 8)
        {
          return static_cast<T>(_mm_extract_epi64(v0, V));
        }
      }
      else
      {
        if constexpr(sizeof(T) == 1)
        {
          return static_cast<T>((_mm_extract_epi16(v0, V / 2) >> (8 * (V % 2))) & 0xFF);
        }
        else if constexpr(sizeof(T) == 4)
        {
          return _mm_cvtsi128_si32(_mm_srli_si128(v0, 4 * V));
        }
        else if constexpr(sizeof(T) == 8)
        {
          return _mm_cvtsi128_si64(_mm_srli_si128(v0, 8 * V));
        }
      }
    }
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE logical<T> extract_(EVE_SUPPORTS(sse2_),
                                      logical<wide<T, N, sse_>> const &   v0,
                                      std::integral_constant<I, V> const &u) noexcept
  {
    return logical<T>(extract(v0.bits(), u));
  }
}

