//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_NOTAND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_NOTAND_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bitwise_notand.hpp>

#if defined(EVE_HW_X86)
#if EVE_HW_X86 >= EVE_SSE2_VERSION
  #include <eve/module/core/function/simd/x86/sse2/bitwise_notand.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
  #include <eve/module/core/function/simd/x86/avx/bitwise_notand.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX2_VERSION
  #include <eve/module/core/function/simd/x86/avx2/bitwise_notand.hpp>
#endif

#endif

#if defined(EVE_HW_POWERPC)
#if EVE_HW_POWERPC >= EVE_VMX_VERSION
#include <eve/module/core/function/simd/ppc/vmx/bitwise_notand.hpp>
#endif
#endif

#if defined(EVE_HW_ARM)
#if EVE_HW_ARM >= EVE_NEON_VERSION
#include <eve/module/core/function/simd/arm/neon/bitwise_notand.hpp>
#endif
#endif

#endif
