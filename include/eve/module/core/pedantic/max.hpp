//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/pedantic/impl/max.hpp>
#include <eve/module/core/regular/max.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/pedantic/impl/simd/arm/neon/max.hpp>
#endif
