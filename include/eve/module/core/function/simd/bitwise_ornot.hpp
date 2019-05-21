//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_ORNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_ORNOT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bitwise_ornot.hpp>

#if defined(EVE_HW_ARM)
#  if EVE_HW_ARM >= EVE_NEON_VERSION
#    include <eve/module/core/function/simd/arm/neon/bitwise_ornot.hpp>
#  endif
#endif

#endif
