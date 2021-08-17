//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/max.hpp>
#include <eve/module/real/core/function/pedantic/generic/max.hpp>


#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/pedantic/simd/arm/neon/max.hpp>
#endif
