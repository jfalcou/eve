//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_FMA4_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_FMA4_SPEC_HPP_INCLUDED

#if defined(EVE_SUPPORTS_FMA4)
  #if defined(_MSC_VER)
    #include <intrin.h>
  #else
    #include <x86intrin.h>
    #include <fma4intrin.h>
  #endif
#endif

#endif
