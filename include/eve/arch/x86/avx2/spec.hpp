//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX2_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_AVX2_SPEC_HPP_INCLUDED

#include <eve/arch/x86/avx2/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_HW_X86 == EVE_AVX2_VERSION
    #define EVE_CURRENT_ABI ::eve::avx_
    #define EVE_CURRENT_API ::eve::avx2_
  #endif
#endif

#if EVE_HW_X86 >= EVE_AVX2_VERSION
  #include <immintrin.h>
  #include <eve/arch/x86/avx/abi_of.hpp>
  #include <eve/arch/x86/avx/as_register.hpp>
#endif

#endif
