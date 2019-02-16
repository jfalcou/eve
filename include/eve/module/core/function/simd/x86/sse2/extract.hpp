//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_EXTRACT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve ::detail
{
  template<typename T, typename N, typename I, auto val>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(sse2_),
                             wide<T, N, sse_> const &v0,
                             std::integral_constant<I, val> const &) noexcept
  {
    using i_t =  std::integral_constant<I, val>;
    enum { idx = i_t::value };

    if constexpr(sizeof(T) == 1)
    {
      int v = _mm_extract_epi16(v0, idx / 2);
      return (v >> (8*(idx % 2)))& 0xFF;
    }

    if constexpr(sizeof(T) == 2)
    {
      return static_cast<T>(_mm_extract_epi16(v0, idx));
    }

    if constexpr(sizeof(T) == 4 && std::is_integral_v<T>)
    {
      return _mm_cvtsi128_si32(_mm_srli_si128(v0, idx * 4));
    }

#if defined(EVE_ARCH_IS_X86_64)

    if constexpr(sizeof(T) == 4 && std::is_floating_point_v<T>)
    {
      return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v0), i_t::value * 4)));
    }

    if constexpr(sizeof(T) == 8)
    {
      if constexpr(std::is_integral_v<T>)
      {
        return _mm_cvtsi128_si64(_mm_srli_si128(v0, idx * 8));
      }
      else
      {
        return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v0), idx * 8)));
      }
    }
#elif defined(EVE_ARCH_IS_X86_32)

    if constexpr((sizeof(T) == 4 && std::is_floating_point_v<T>) || (sizeof(T) == 8))
    { return v0[ idx ]; }
#endif
  }

}

#endif
