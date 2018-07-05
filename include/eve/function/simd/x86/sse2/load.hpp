//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SIMD_X86_SSE2_LOAD_HPP_INCLUDED
#define EVE_FUNCTION_SIMD_X86_SSE2_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  //------------------------------------------------------------------------------------------------
  // double case 1->2
  template<typename N>
  EVE_FORCEINLINE __m128d load(as_<pack<double,N>> const&, eve::sse_ const&, double* ptr) noexcept
  {
    return _mm_loadu_pd(ptr);
  }

  //------------------------------------------------------------------------------------------------
  // float case 1->4
  template<typename N>
  EVE_FORCEINLINE __m128 load(as_<pack<float,N>> const&, eve::sse_ const&, float* ptr) noexcept
  {
    return _mm_loadu_ps(ptr);
  }

  //------------------------------------------------------------------------------------------------
  // *int* case 1->N
  template<typename T, typename N>
  EVE_FORCEINLINE std::enable_if_t<std::is_integral_v<T>,__m128i>
  load(as_<pack<T,N>> const&, eve::sse_ const&, T* ptr) noexcept
  {
    return _mm_loadu_si128((__m128i*)ptr);
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
