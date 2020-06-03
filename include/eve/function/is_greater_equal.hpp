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

#include <eve/function/definition/is_greater_equal.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/is_greater_equal.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/is_greater_equal.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/is_greater_equal.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/is_greater_equal.hpp>
#endif

