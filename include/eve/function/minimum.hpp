//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(minimum_, minimum);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/minimum.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_HW_X86)
#  include <eve/module/real/algorithm/function/regular/simd/x86/minimum.hpp>
#endif
