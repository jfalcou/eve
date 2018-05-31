//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED

#include <eve/arch/x86/sse4_1/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_SIMD_X86 == EVE_SSE4_1_VERSION
    #define EVE_CURRENT_ABI ::eve::sse_
    #define EVE_CURRENT_API ::eve::sse4_1_
  #endif
#endif

#if EVE_SIMD_X86 >= EVE_SSE4_1_VERSION
  #include <smmintrin.h>
#endif

#endif
