//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_FNMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_FNMA_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/fnma.hpp>

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#   if defined(EVE_SUPPORTS_FNMA3)
#    include <eve/module/core/function/simd/x86/fnma3/fnma.hpp>
#   endif
#   if defined(EVE_SUPPORTS_FNMA4) || defined(EVE_SUPPORTS_XOP)
#    include <eve/module/core/function/simd/x86/fnma4/fnma.hpp>
#   endif
#  endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/fnma.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/fnma.hpp>
#  endif
#endif

#endif
