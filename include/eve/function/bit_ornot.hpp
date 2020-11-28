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
  EVE_MAKE_CALLABLE(bit_ornot_, bit_ornot);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/bit_ornot.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/bit_ornot.hpp>
#endif


