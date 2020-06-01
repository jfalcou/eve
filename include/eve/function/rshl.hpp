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

#include <eve/function/definition/rshl.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/rshl.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/rshl.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/rshl.hpp>
#endif
