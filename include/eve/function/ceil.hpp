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
  EVE_MAKE_CALLABLE(ceil_, ceil);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/ceil.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/ceil.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/regular/simd/ppc/ceil.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/ceil.hpp>
#endif

