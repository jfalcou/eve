//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/pedantic/min.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/pedantic/impl/simd/arm/neon/min.hpp>
#endif
