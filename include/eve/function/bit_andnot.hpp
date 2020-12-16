//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(bit_andnot_, bit_andnot);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_andnot.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/core/function/regular/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/real/core/function/regular/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/regular/simd/arm/neon/bit_andnot.hpp>
#endif

