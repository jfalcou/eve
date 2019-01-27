//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMPLEMENT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMPLEMENT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/complement.hpp>

#if defined(EVE_HW_POWERPC)
#if EVE_HW_POWERPC >= EVE_VMX_VERSION
#include <eve/module/core/function/simd/ppc/vmx/complement.hpp>
#endif
#endif

#if defined(EVE_HW_ARM)
#if EVE_HW_ARM >= EVE_NEON_VERSION
#include <eve/module/core/function/simd/arm/neon/complement.hpp>
#endif
#endif

#endif
