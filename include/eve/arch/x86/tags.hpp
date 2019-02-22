//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
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

// AVX ABI
#include <eve/arch/x86/avx/tags.hpp>
#include <eve/arch/x86/fma3/tags.hpp>
#include <eve/arch/x86/xop/tags.hpp>
#include <eve/arch/x86/fma4/tags.hpp>
#include <eve/arch/x86/avx2/tags.hpp>

// AVX512 ABI
//#include <eve/arch/x86/avx512/tags.hpp>

#endif
