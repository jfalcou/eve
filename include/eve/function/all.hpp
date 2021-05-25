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
  EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/all.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/module/real/algorithm/function/regular/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/all.hpp>
#endif
