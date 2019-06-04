//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ABS_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/abs.hpp>

#if defined(EVE_HW_X86)

#  if EVE_HW_X86 >= EVE_SSSE3_VERSION
#    include <eve/module/core/function/simd/x86/ssse3/abs.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/module/core/function/simd/x86/avx/abs.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX2_VERSION
#    include <eve/module/core/function/simd/x86/avx2/abs.hpp>
#  endif

#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/abs.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/abs.hpp>
#  endif
#endif

#endif
