//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/function/definition/nearest.hpp>
#include <eve/module/core/function/generic/nearest.hpp>

#  if defined(EVE_HW_X86)
#    include <eve/module/core/function/simd/x86/nearest.hpp>
#  endif

#  if defined(EVE_HW_POWERPC)
#    include <eve/module/core/function/simd/ppc/nearest.hpp>
#  endif

#  if defined(EVE_HW_ARM)
#    include <eve/module/core/function/simd/arm/neon/nearest.hpp>
#  endif

