//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/pedantic/max.hpp>


#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/pedantic/impl/simd/arm/neon/max.hpp>
#endif
