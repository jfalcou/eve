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

#include <eve/function/definition/bit_notor.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/bit_notor.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/bit_notor.hpp>
#endif

