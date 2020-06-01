//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_LOG2_HPP_INCLUDED
#define EVE_FUNCTION_LOG2_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/function/definition/log2.hpp>
#include <eve/module/core/function/generic/log2.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/math/function/simd/x86/log2.hpp>
#endif

#endif
