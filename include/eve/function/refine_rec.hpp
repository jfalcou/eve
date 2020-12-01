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
  EVE_MAKE_CALLABLE(refine_rec_, refine_rec);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/refine_rec.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/refine_rec.hpp>
#endif

