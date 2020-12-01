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
#include <eve/module/core/function/pedantic/generic/fnma.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/pedantic/simd/x86/fnma.hpp>
#endif
