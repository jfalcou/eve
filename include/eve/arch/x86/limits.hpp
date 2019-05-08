//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_LIMITS_HPP_INCLUDED

// SSE ABI
#include <eve/arch/x86/sse2/limits.hpp>
#include <eve/arch/x86/sse3/limits.hpp>
#include <eve/arch/x86/ssse3/limits.hpp>
#include <eve/arch/x86/sse4_1/limits.hpp>
#include <eve/arch/x86/sse4_2/limits.hpp>

// AVX ABI
#include <eve/arch/x86/avx/limits.hpp>
#include <eve/arch/x86/avx2/limits.hpp>

// AVX512 ABI
//#include <eve/arch/x86/avx512/limits.hpp>

#endif
