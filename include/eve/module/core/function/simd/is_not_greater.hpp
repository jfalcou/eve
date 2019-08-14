//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IS_NOT_GREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IS_NOT_GREATER_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/is_not_greater.hpp>


#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/is_not_greater.hpp>
#endif

#endif
