//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_SPEC_HPP_INCLUDED

#include <eve/arch/x86/sse2/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_HW_X86 == EVE_SSE2_VERSION
    #define EVE_CURRENT_ABI ::eve::sse_
    #define EVE_CURRENT_API ::eve::sse2_
  #endif
#endif

#if EVE_HW_X86 >= EVE_SSE2_VERSION
  #include <xmmintrin.h>
  #include <eve/arch/x86/sse2/abi_of.hpp>
  #include <eve/arch/x86/sse2/as_register.hpp>
#endif

#endif
