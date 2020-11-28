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
  EVE_MAKE_CALLABLE(is_not_less_equal_, is_not_less_equal);
}

#include <eve/module/core/function/regular/generic/is_not_less_equal.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/is_not_less.hpp>
#endif

