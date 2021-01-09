//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/min.hpp>
#include <eve/module/real/core/function/pedantic/generic/min.hpp>

#if defined(EVE_HW_ARM)
#  include <eve/module/real/core/function/pedantic/simd/arm/neon/min.hpp>
#endif
