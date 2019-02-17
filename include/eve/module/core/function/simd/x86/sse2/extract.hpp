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
#include <eve/function/bitwise_cast.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve ::detail
{
  template<typename T, typename N,typename I, auto V>
  EVE_FORCEINLINE auto extract_ ( EVE_SUPPORTS(sse2_),
                                        wide<logical<T>, N, sse_> const &v0,
                                        std::integral_constant<I, V> const& u) noexcept
  {
    return bitwise_cast<logical<T>>( extract( bitwise_cast<wide<T,N>>(v0), u) );
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(sse2_),
                             wide<T, N, sse_> const &v0,
                             std::integral_constant<I, V> const &) noexcept
  {
    constexpr auto qv = 4 * V;
    constexpr auto ov = 8 * V;

    static_assert((V < wide<T, N, sse_>::static_size),
                  "[EVE} - extract : Index is out of bound for current architecture");

    if constexpr(sizeof(T) == 1)
    {
      int v = _mm_extract_epi16(v0, V / 2);
      return static_cast<T>((v >> (8 * (V % 2))) & 0xFF);
    }

    if constexpr(sizeof(T) == 2) { return static_cast<T>(_mm_extract_epi16(v0, V)); }

    if constexpr(sizeof(T) == 4)
    {
      if constexpr(std::is_integral_v<T>) return _mm_cvtsi128_si32(_mm_srli_si128(v0, qv));

      if constexpr(std::is_floating_point_v<T>)
      {
#if defined(EVE_ARCH_IS_X86_64)
        return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v0), qv)));
#else
        return v0[ V ];
#endif
      }
    }

    if constexpr(sizeof(T) == 8)
    {
      if constexpr(std::is_integral_v<T>) return _mm_cvtsi128_si64(_mm_srli_si128(v0, ov));

      if constexpr(std::is_floating_point_v<T>)
      {
#if defined(EVE_ARCH_IS_X86_64)
        return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v0), ov)));
#else
        return v0[ V ];
#endif
      }
    }
  }
}

#endif
