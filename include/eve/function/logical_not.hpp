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
  EVE_MAKE_CALLABLE(logical_not_, logical_not);
}

#include <eve/module/real/core/function/regular/generic/logical_not.hpp>

#if defined(EVE_HW_X86)
#include <eve/module/real/core/function/regular/simd/x86/logical_not.hpp>
#endif
