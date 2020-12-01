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
  EVE_MAKE_CALLABLE(is_lessgreater_, is_lessgreater);
}

#include <eve/module/core/function/regular/generic/is_lessgreater.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/is_lessgreater.hpp>
#endif

