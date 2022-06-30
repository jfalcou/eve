//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <cstdint>
#include <cstddef>

//==================================================================================================
// X86 hardware info
# if defined(SPY_SIMD_IS_X86)
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 2 * sizeof(void *);
    static constexpr std::size_t simd    = 2 * sizeof(void *);
  };
}

//==================================================================================================
// X86 SIMD API/ABI
# if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_X86)
#  include <immintrin.h>
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_AVX512)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_512_
#    define EVE_CURRENT_API ::eve::avx512_
#    define EVE_ABI_NAMESPACE avx512_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_AVX2)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_256_
#    define EVE_CURRENT_API ::eve::avx2_
#    define EVE_ABI_NAMESPACE avx_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_AVX)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_256_
#    define EVE_CURRENT_API ::eve::avx_
#    define EVE_ABI_NAMESPACE avx_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_SSE4_2)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_128_
#    define EVE_CURRENT_API ::eve::sse4_2_
#    define EVE_ABI_NAMESPACE sse_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_SSE4_1)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_128_
#    define EVE_CURRENT_API ::eve::sse4_1_
#    define EVE_ABI_NAMESPACE sse_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_SSSE3)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_128_
#    define EVE_CURRENT_API ::eve::ssse3_
#    define EVE_ABI_NAMESPACE sse_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_SSE3)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_128_
#    define EVE_CURRENT_API ::eve::sse3_
#    define EVE_ABI_NAMESPACE sse_abi_v0
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_X86_SSE2)
#    define EVE_ABI_DETECTED
#    define EVE_CURRENT_ABI ::eve::x86_128_
#    define EVE_CURRENT_API ::eve::sse2_
#    define EVE_ABI_NAMESPACE sse_abi_v0
#  endif
# endif

// TODO: AVX512 API
# endif

//==================================================================================================
// Additionnal ISA support
#if defined(SPY_SIMD_SUPPORTS_FMA)
#  include <immintrin.h>
#endif
