//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IS_LEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IS_LEZ_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/is_lez.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/module/core/function/simd/x86/sse2/is_lez.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_SEE4_2_VERSION
#    include <eve/module/core/function/simd/x86/sse4_2/is_lez.hpp>
#  endif

#endif

#endif
