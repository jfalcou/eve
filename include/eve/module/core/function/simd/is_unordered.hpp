//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_IS_UNORDERED_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_IS_UNORDERED_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/is_unordered.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/simd/x86/is_unordered.hpp>
#endif

#endif

