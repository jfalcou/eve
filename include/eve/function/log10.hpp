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

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(log10_, log10);
}

#include <eve/module/math/function/regular/generic/log10.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/math/function/regular/simd/x86/log10.hpp>
#endif

