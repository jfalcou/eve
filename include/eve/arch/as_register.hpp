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

#include <eve/arch/cpu/as_register.hpp>

#if !defined(EVE_NO_SIMD)
#include <eve/arch/x86/as_register.hpp>
#include <eve/arch/ppc/as_register.hpp>
#include <eve/arch/arm/as_register.hpp>
#endif

