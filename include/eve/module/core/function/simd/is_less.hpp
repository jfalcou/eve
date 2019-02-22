//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IS_LESS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IS_LESS_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/is_less.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/module/core/function/simd/x86/sse2/is_less.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_SSE4_2_VERSION
#    include <eve/module/core/function/simd/x86/sse4_2/is_less.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/module/core/function/simd/x86/avx/is_less.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX2_VERSION
#    include <eve/module/core/function/simd/x86/avx2/is_less.hpp>
#  endif

#endif

// #if defined(EVE_HW_POWERPC)
// #  if EVE_HW_POWERPC >= EVE_VMX_VERSION
// #    include <eve/module/core/function/simd/ppc/vmx/is_less.hpp>
// #  endif
// #endif

// #if defined(EVE_HW_ARM)
// #  if EVE_HW_ARM >= EVE_NEON_VERSION
// #    include <eve/module/core/function/simd/arm/neon/is_less.hpp>
// #  endif
// #endif

#endif
