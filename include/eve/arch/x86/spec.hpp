//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SPEC_HPP_INCLUDED

#include <eve/detail/compiler.hpp>
#include <eve/arch/x86/predef.hpp>
#include <cstdint>
#include <cstddef>

//==================================================================================================
// X86 hardware info
#if defined(EVE_HW_X86)
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 2 * sizeof(void *);
    static constexpr std::size_t simd    = 2 * sizeof(void *);
  };
}

//==================================================================================================
// X86 SIMD ABI
#  if !defined(EVE_CURRENT_ABI)
#    include <immintrin.h>
#    if EVE_HW_X86 >= EVE_AVX_VERSION
#      define EVE_CURRENT_ABI ::eve::avx_
#    elif EVE_HW_X86 >= EVE_SSE2_VERSION
#      define EVE_CURRENT_ABI ::eve::sse_
#    endif
#  endif
#endif

// TODO: AVX512 ABI

//==================================================================================================
// X86 SIMD API
#if !defined(EVE_CURRENT_API) && EVE_HW_X86
#  if EVE_HW_X86 == EVE_SSE2_VERSION
#    define EVE_CURRENT_API ::eve::sse2_
#  elif EVE_HW_X86 == EVE_SSE3_VERSION
#    define EVE_CURRENT_API ::eve::sse3_
#  elif EVE_HW_X86 == EVE_SSSE3_VERSION
#    define EVE_CURRENT_API ::eve::ssse3_
#  elif EVE_HW_X86 == EVE_SSE4_1_VERSION
#    define EVE_CURRENT_API ::eve::sse4_1_
#  elif EVE_HW_X86 == EVE_SSE4_2_VERSION
#    define EVE_CURRENT_API ::eve::sse4_2_
#  elif EVE_HW_X86 == EVE_AVX_VERSION
#    define EVE_CURRENT_API ::eve::avx_
#  elif EVE_HW_X86 == EVE_AVX2_VERSION
#    define EVE_CURRENT_API ::eve::avx2_
#  endif
#endif

// TODO: AVX512 API

#endif
