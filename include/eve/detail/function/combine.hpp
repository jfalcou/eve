//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DETAIL_COMBINE_HPP_INCLUDED
#define EVE_FUNCTION_DETAIL_COMBINE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/combine.hpp>

#if defined(EVE_HW_X86)
#if EVE_HW_X86 >= EVE_SSE2_VERSION
#include <eve/detail/function/simd/x86/sse2/combine.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
#include <eve/detail/function/simd/x86/avx/combine.hpp>
#endif
#endif

#if defined(EVE_HW_POWERPC)
#if EVE_HW_POWERPC >= EVE_VMX_VERSION
#include <eve/detail/function/simd/ppc/vmx/combine.hpp>
#endif
#endif

#endif
