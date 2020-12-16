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
  EVE_MAKE_CALLABLE(is_greater_, is_greater);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/is_greater.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/regular/simd/x86/is_greater.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/real/core/function/regular/simd/ppc/is_greater.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/is_greater.hpp>
#endif

