//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_EXTRACT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/extract.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/module/core/function/simd/x86/sse2/extract.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_SSE4_1_VERSION
#    include <eve/module/core/function/simd/x86/sse4_1/extract.hpp>
#  endif

#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/extract.hpp>
#  endif
#endif

#endif
