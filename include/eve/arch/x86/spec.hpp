//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <cstdint>
#include <cstddef>

//==================================================================================================
// X86 hardware info
EVE_NAMESPACE
{
  struct register_count
  {
    static constexpr std::size_t general = 2 * sizeof(void *);
    static constexpr std::size_t simd    = 2 * sizeof(void *);
  };
}

//==================================================================================================
// X86 SIMD API/ABI
#include <immintrin.h>

#if defined(SPY_SIMD_IS_X86_AVX512)
#  define EVE_CURRENT_ABI ::eve::x86_512_
#  define EVE_CURRENT_API ::eve::avx512_
#elif defined(SPY_SIMD_IS_X86_AVX2)
#  define EVE_CURRENT_ABI ::eve::x86_256_
#  define EVE_CURRENT_API ::eve::avx2_
#elif defined(SPY_SIMD_IS_X86_AVX)
#  define EVE_CURRENT_ABI ::eve::x86_256_
#  define EVE_CURRENT_API ::eve::avx_
#elif defined(SPY_SIMD_IS_X86_SSE4_2)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse4_2_
#elif defined(SPY_SIMD_IS_X86_SSE4_1)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse4_1_
#elif defined(SPY_SIMD_IS_X86_SSSE3)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::ssse3_
#elif defined(SPY_SIMD_IS_X86_SSE3)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse3_
#elif defined(SPY_SIMD_IS_X86_SSE2)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse2_
#endif
