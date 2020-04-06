//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_MAX_HPP_INCLUDED
#define EVE_FUNCTION_MAX_HPP_INCLUDED

#include <eve/function/definition/max.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/max.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/max.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/max.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/max.hpp>
#endif

#endif
