//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IS_UNORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IS_UNORDERED_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/is_unordered.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/module/core/function/simd/x86/sse2/is_unordered.hpp>
#  endif
#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/module/core/function/simd/x86/avx/is_unordered.hpp>
#  endif
#endif

#endif

