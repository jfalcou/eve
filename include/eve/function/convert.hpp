//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_CONVERT_HPP_INCLUDED
#define EVE_FUNCTION_CONVERT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/function/definition/convert.hpp>
#include <eve/module/core/function/generic/convert.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/convert.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/convert.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/convert.hpp>
#endif

#endif
