//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

#if defined(SPY_SIMD_IS_ARM_FIXED_SVE) || defined(SPY_SIMD_IS_ARM_FIXED_SVE2)
#  define EVE_SIMD_IS_ANY_FIXED_SVE
#endif
