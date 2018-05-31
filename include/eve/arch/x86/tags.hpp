//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_TAGS_HPP_INCLUDED

// SSE ABI
#include <eve/arch/x86/sse2/tags.hpp>
#include <eve/arch/x86/sse3/tags.hpp>
#include <eve/arch/x86/ssse3/tags.hpp>
#include <eve/arch/x86/sse4_1/tags.hpp>
#include <eve/arch/x86/sse4_2/tags.hpp>
#include <eve/arch/x86/sse4a/tags.hpp>

// AVX ABI
#include <eve/arch/x86/avx/tags.hpp>
#include <eve/arch/x86/fma3/tags.hpp>
#include <eve/arch/x86/xop/tags.hpp>
#include <eve/arch/x86/fma4/tags.hpp>
#include <eve/arch/x86/avx2/tags.hpp>

// AVX512 ABI
//#include <eve/arch/x86/avx512/tags.hpp>

#endif
