//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU 
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IFNOT_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IFNOT_ELSE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/ifnot_else.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION 
#    include <eve/module/core/function/simd/x86/sse2/ifnot_else.hpp>
#  endif
#  if EVE_HW_X86 >= EVE_SSE4_1_VERSION 
#    include <eve/module/core/function/simd/x86/sse4_1/ifnot_else.hpp>
#  endif
#  if (EVE_HW_X86 >= EVE_AVX_VERSION)
#    include <eve/module/core/function/simd/x86/avx/ifnot_else.hpp>
#  endif
#  if EVE_HW_X86 >= EVE_AVX2_VERSION
#    include <eve/module/core/function/simd/x86/avx2/ifnot_else.hpp>
#  endif 
#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/ifnot_else.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/ifnot_else.hpp>
#  endif
#endif
#endif
