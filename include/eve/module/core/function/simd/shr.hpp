//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SHR_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/shr.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/module/core/function/simd/x86/sse2/shr.hpp>
#  endif

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_AVX_VERSION
#   if defined(EVE_SUPPORTS_XOP)
#    include <eve/module/core/function/simd/x86/xop/shr.hpp>
#   endif
#  endif
#endif

#  if EVE_HW_X86 >= EVE_AVX2_VERSION
#    include <eve/module/core/function/simd/x86/avx2/shr.hpp>
#  endif

#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/shr.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/shr.hpp>
#  endif
#endif

#endif
