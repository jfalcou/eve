//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BIT_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BIT_NOT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bit_not.hpp>

#if defined(EVE_HW_POWERPC)
#  if EVE_HW_POWERPC >= EVE_VMX_VERSION
#    include <eve/module/core/function/simd/ppc/bit_not.hpp>
#  endif
#endif

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/bit_not.hpp>
#  endif
#endif

#endif
