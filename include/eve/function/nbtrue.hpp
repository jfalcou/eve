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
  EVE_MAKE_CALLABLE(nbtrue_, nbtrue);
}

#include <eve/arch.hpp>
#include <eve/module/algorithm/function/regular/generic/nbtrue.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/algorithm/function/regular/simd/x86/nbtrue.hpp>
#endif

