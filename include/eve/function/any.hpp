//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(any_, any);
}

#include <eve/arch.hpp>
#include <eve/module/algorithm/function/generic/any.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/algorithm/function/simd/x86/any.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/algorithm/function/simd/ppc/any.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/algorithm/function/simd/arm/neon/any.hpp>
#endif

