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
  EVE_MAKE_CALLABLE(bit_not_, bit_not);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/bit_not.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/bit_not.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/simd/arm/neon/bit_not.hpp>
#endif

