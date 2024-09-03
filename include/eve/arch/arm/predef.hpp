//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

// We successfully detected some native SIMD
#if (defined(SPY_SIMD_IS_ARM_FIXED_SVE) || defined(SPY_SIMD_IS_ARM_FIXED_SVE2)) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_ARM_SVE
#  define EVE_INCLUDE_SVE_HEADER
#elif defined(SPY_SIMD_IS_ARM) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_ARM
#  define EVE_INCLUDE_ARM_HEADER
#endif
