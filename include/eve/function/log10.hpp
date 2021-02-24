//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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

#include <eve/module/real/math/function/regular/generic/log10.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/real/math/function/regular/simd/x86/log10.hpp>
#endif

