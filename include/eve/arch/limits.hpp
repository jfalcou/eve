//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_LIMITS_HPP_INCLUDED
#define EVE_ARCH_LIMITS_HPP_INCLUDED

#include <eve/arch/cpu/limits.hpp>

#if !defined(EVE_NO_SIMD)
#include <eve/arch/x86/limits.hpp>
#include <eve/arch/ppc/limits.hpp>
#include <eve/arch/arm/limits.hpp>
#endif

#endif
