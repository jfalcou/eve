//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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
