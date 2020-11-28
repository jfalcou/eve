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
  EVE_MAKE_CALLABLE(frac_, frac);
}

#include <eve/module/core/function/regular/generic/frac.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/frac.hpp>
#endif
