//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DETAIL_MAKE_HPP_INCLUDED
#define EVE_FUNCTION_DETAIL_MAKE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/make.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/detail/function/simd/x86/sse2/make.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/detail/function/simd/x86/avx/make.hpp>
#  endif
#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/detail/function/simd/ppc/vmx/make.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/detail/function/simd/arm/neon/make.hpp>
#  endif
#endif

#endif
