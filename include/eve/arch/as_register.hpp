//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/as_register.hpp>

#if !defined(EVE_NO_SIMD)
#include <eve/arch/x86/as_register.hpp>
#include <eve/arch/ppc/as_register.hpp>
#include <eve/arch/arm/sve/as_register.hpp>
#include <eve/arch/arm/neon/as_register.hpp>
#endif

