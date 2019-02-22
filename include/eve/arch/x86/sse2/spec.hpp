//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_SPEC_HPP_INCLUDED

#include <eve/arch/x86/sse2/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
#  if EVE_HW_X86 == EVE_SSE2_VERSION
#    define EVE_CURRENT_ABI ::eve::sse_
#    define EVE_CURRENT_API ::eve::sse2_
#  endif
#endif

#if EVE_HW_X86 >= EVE_SSE2_VERSION
#  include <xmmintrin.h>
#endif

#endif
