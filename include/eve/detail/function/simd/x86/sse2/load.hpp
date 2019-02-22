//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_LOAD_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &,
                            eve::sse_ const &,
                            T *p) noexcept requires(typename wide<T, N>::storage_type,
                                                    Arithmetic<T>)
  {
    if constexpr(std::is_same_v<T, double>) return _mm_loadu_pd(p);
    if constexpr(std::is_same_v<T, float>) return _mm_loadu_ps(p);
    if constexpr(std::is_integral_v<T>) return _mm_loadu_si128((__m128i *)p);
  }

  template<typename T, typename N, std::size_t A>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt,
       eve::sse_ const &      mode,
       aligned_ptr<T, A>      p) noexcept requires(typename wide<T, N>::storage_type, Arithmetic<T>)
  {
    if constexpr(A >= 16)
    {
      if constexpr(std::is_same_v<T, double>) return _mm_load_pd(p.get());
      if constexpr(std::is_same_v<T, float>) return _mm_load_ps(p.get());
      if constexpr(std::is_integral_v<T>) return _mm_load_si128((__m128i *)p.get());
    }
    else
    {
      return load(tgt, mode, p.get());
    }
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
