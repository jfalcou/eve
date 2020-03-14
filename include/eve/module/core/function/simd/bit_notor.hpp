//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_BIT_NOTOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_BIT_NOTOR_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/module/core/function/simd/common/bit_notor.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/bit_notor.hpp>
#endif

#endif
