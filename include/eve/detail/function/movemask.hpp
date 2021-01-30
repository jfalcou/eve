//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Dens YAROSHEVKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/movemask.hpp>
#endif
