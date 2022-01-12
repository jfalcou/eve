//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/pedantic/max.hpp>


#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/arithmetic/pedantic/impl/simd/arm/neon/max.hpp>
#endif
