//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BITWISE_SELECT_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bitwise_select.hpp>

#if defined(EVE_HW_X86)

#  if defined(EVE_SUPPORTS_XOP)
#    include <eve/module/core/function/simd/x86/xop/bitwise_select.hpp>
#  endif

#endif

#endif
