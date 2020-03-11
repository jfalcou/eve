//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_UNARY_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_UNARY_MINUS_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/unary_minus.hpp>

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/unary_minus.hpp>
#  endif
#endif

#endif
