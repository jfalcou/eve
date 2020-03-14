//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SPEC_HPP_INCLUDED

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

// TODO: AVX512 ABI

//==================================================================================================
// X86 SIMD API/ABI
# if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_X86)
#  include <immintrin.h>
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_AVX2)
#    define EVE_CURRENT_ABI ::eve::avx_
#    define EVE_CURRENT_API ::eve::avx2_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_AVX)
#    define EVE_CURRENT_ABI ::eve::avx_
#    define EVE_CURRENT_API ::eve::avx_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_SSE4_2)
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::sse4_2_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_SSE4_1)
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::sse4_1_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_SSSE3)
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::ssse3_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_SSE3)
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::sse3_
#  endif
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_X86_SSE2)
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::sse2_
#  endif
# endif

// TODO: AVX512 API
# endif

//==================================================================================================
// Additionnal ISA support
#if defined(SPY_SIMD_SUPPORTS_FMA)
#  include <immintrin.h>
#endif

#if defined(SPY_SIMD_SUPPORTS_FMA4)
#  if defined(SPY_COMPILER_IS_MSVC)
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    include <fma4intrin.h>
#  endif
#endif

#if defined(SPY_SIMD_SUPPORTS_XOP)
#  if defined(SPY_COMPILER_IS_MSVC)
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    include <xopintrin.h>
#  endif
#endif

#endif
