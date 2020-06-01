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

#include <eve/function/definition/is_lessgreater.hpp>
#include <eve/module/core/function/generic/is_lessgreater.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/is_lessgreater.hpp>
#endif

