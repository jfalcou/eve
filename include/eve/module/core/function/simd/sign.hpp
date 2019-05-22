//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SIGN_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/sign.hpp>

#if defined(EVE_HW_X86)

#  if EVE_HW_X86 >= EVE_SSSE3_VERSION
#    include <eve/module/core/function/simd/x86/ssse3/abs.hpp>
#  endif

#endif
#endif
 
