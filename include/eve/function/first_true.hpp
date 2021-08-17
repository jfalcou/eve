//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(first_true_, first_true);
}

#include <eve/arch.hpp>
#include <eve/module/real/algorithm/function/regular/generic/first_true.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/algorithm/function/regular/simd/arm/neon/first_true.hpp>
#endif
