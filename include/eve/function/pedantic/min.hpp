//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/min.hpp>
#include <eve/module/real/core/function/pedantic/generic/min.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/pedantic/simd/arm/neon/min.hpp>
#endif
