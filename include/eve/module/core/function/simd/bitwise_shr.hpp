//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_SHR_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bitwise_shr.hpp>

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/vmx/bitwise_shr.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/bitwise_shr.hpp>
#  endif
#endif

#endif
