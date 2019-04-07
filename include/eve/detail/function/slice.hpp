//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SLICE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/slice.hpp>

#if defined(EVE_HW_X86)
#  if EVE_HW_X86 >= EVE_SSE2_VERSION
#    include <eve/detail/function/simd/x86/sse2/slice.hpp>
#  endif

#  if EVE_HW_X86 >= EVE_AVX_VERSION
#    include <eve/detail/function/simd/x86/avx/slice.hpp>
#  endif
#endif

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/detail/function/simd/ppc/vmx/slice.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/detail/function/simd/arm/neon/slice.hpp>
#  endif
#endif

#endif
