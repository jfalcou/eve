//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_EXTRACT_HPP_INCLUDED

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
  EVE_FORCEINLINE auto extract_ ( EVE_SUPPORTS(sse4_1_),
                                        wide<logical<T>, N, sse_> const &v0,
                                        std::integral_constant<I, V> const& u) noexcept
  {
    return bitwise_cast<logical<T>>( extract( bitwise_cast<wide<T,N>>(v0), u) );
  }

  template<typename T, typename N, typename I, auto V>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(sse4_1_),
                             wide<T, N, sse_> const &v0,
                             std::integral_constant<I, V> const &) noexcept
  {
    constexpr auto qi = 4 * idx_<V>::value;
    constexpr auto oi = 8 * idx_<V>::value;

    static_assert((V < wide<T, N, sse_>::static_size),
                  "[EVE} - extract : Index is out of bound for current architecture");

    if constexpr(sizeof(T) == 1) return static_cast<T>(_mm_extract_epi8(v0, idx_<V>::value));
    if constexpr(sizeof(T) == 2) return static_cast<T>(_mm_extract_epi16(v0, idx_<V>::value));

    if constexpr(sizeof(T) == 4)
    {
      if constexpr(std::is_integral_v<T>)
        return static_cast<T>(_mm_extract_epi32(v0, idx_<V>::value));

      if constexpr(std::is_floating_point_v<T>)
      {
#ifdef EVE_ARCH_IS_X86_64
        return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v0), qi)));
#else
        float f;
        _MM_EXTRACT_FLOAT(f, v0, idx_<V>::value);
        return f;
#endif
      }
    }

    if constexpr(sizeof(T) == 8)
    {
      if constexpr(std::is_integral_v<T>)
      {
#if defined(EVE_COMP_IS_MSVC)
        return _mm_extract_epi64(v0, idx_<V>::value);
#else
#  if defined(EVE_ARCH_IS_X86_64)
        return _mm_cvtsi128_si64(_mm_srli_si128(v0, oi));
#  else
        return v0[ idx_<V>::value ];
#  endif
#endif
      }

      if constexpr(std::is_floating_point_v<T>)
      {
#if defined(EVE_ARCH_IS_X86_64)
        return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v0), oi)));
#else

        return v0[ idx_<V>::value ];
#endif
      }
    }
  }
}

#endif
