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
  EVE_MAKE_CALLABLE(trunc_, trunc);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/trunc.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/regular/simd/x86/trunc.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/real/core/function/regular/simd/ppc/trunc.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/trunc.hpp>
#endif


