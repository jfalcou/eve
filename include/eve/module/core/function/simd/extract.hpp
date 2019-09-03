//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_EXTRACT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/extract.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/extract.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/extract.hpp>
#endif

#endif
