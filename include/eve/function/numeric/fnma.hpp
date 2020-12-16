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

#include <eve/function/fnma.hpp>
#include <eve/module/real/core/function/numeric/generic/fnma.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/numeric/simd/x86/fnma.hpp>
#endif
