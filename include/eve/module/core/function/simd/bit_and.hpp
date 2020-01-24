//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BIT_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BIT_AND_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bit_and.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/bit_and.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/bit_and.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/bit_and.hpp>
#endif

#endif
