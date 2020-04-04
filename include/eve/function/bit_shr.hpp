//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_BIT_SHR_HPP_INCLUDED
#define EVE_FUNCTION_BIT_SHR_HPP_INCLUDED

#include <eve/function/definition/bit_shr.hpp>
#include <eve/arch.hpp>
#include <eve/module/core/function/generic/bit_shr.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/bit_shr.hpp>
#endif

#endif
