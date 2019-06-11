//==================================================================================================
/**
  EVE - Expressive Vector Engine 
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
 
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_NEAREST_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/nearest.hpp>

#if defined(EVE_HW_X86)

#  if EVE_HW_X86 >= EVE_SSE4_1_VERSION
#    include <eve/module/core/function/simd/x86/sse4_1/nearest.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/module/core/function/simd/x86/avx/nearest.hpp>
#  endif

#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/nearest.hpp>
#  endif

#  if EVE_HW_POWERPC >= EVE_VSX_VERSION
#    include <eve/module/core/function/simd/ppc/vsx/nearest.hpp>
#  endif

#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/nearest.hpp>
#  endif
#endif

#endif
