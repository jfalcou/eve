//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/pedantic/min.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/arithmetic/pedantic/impl/simd/arm/neon/min.hpp>
#endif
