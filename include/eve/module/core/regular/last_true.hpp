//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
EVE_MAKE_CALLABLE(last_true_, last_true);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/last_true.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/last_true.hpp>
#endif
