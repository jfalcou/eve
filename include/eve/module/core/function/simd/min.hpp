//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_MIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_MIN_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/min.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/min.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/vmx/min.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/min.hpp>
#endif

#endif
