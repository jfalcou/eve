//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(first_true_, first_true);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/first_true.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/algorithm/function/regular/simd/x86/first_true.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/first_true.hpp>
#endif
