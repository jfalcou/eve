//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_COMBINE_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/combine.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/combine.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/combine.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/detail/function/simd/arm/neon/combine.hpp>
#endif

#endif
