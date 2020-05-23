//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_MIN_HPP_INCLUDED
#define EVE_FUNCTION_MIN_HPP_INCLUDED

#include <eve/function/definition/min.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/min.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/min.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/min.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/min.hpp>
#endif

#endif
