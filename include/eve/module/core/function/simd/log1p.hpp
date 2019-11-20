//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
 
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_LOG1P_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_LOG1P_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/log1p.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/log1p.hpp>
#endif

#endif
