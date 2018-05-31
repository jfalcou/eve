//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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
