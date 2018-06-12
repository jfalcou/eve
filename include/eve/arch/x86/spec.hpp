//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SPEC_HPP_INCLUDED

#include <eve/arch/x86/predef.hpp>
#include <cstdint>

int data[EVE_HW_X86];

// Register count
#if defined(EVE_HW_X86)
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 2*sizeof(void*);
    static constexpr std::size_t simd    = 2*sizeof(void*);
  };
}
#endif

// SSE ABI
#include <eve/arch/x86/sse2/spec.hpp>
#include <eve/arch/x86/sse3/spec.hpp>
#include <eve/arch/x86/ssse3/spec.hpp>
#include <eve/arch/x86/sse4_1/spec.hpp>
#include <eve/arch/x86/sse4_2/spec.hpp>

// AVX ABI
#include <eve/arch/x86/avx/spec.hpp>
#include <eve/arch/x86/fma3/spec.hpp>
#include <eve/arch/x86/xop/spec.hpp>
#include <eve/arch/x86/fma4/spec.hpp>
#include <eve/arch/x86/avx2/spec.hpp>

// AVX512 ABI
//#include <eve/arch/x86/avx512/spec.hpp>

#endif
