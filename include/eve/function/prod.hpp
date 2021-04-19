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
  EVE_MAKE_CALLABLE(prod_, prod);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/prod.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/prod.hpp>
#endif
