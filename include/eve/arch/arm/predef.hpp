//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(SPY_SIMD_IS_ARM_FIXED_SVE) || defined(SPY_SIMD_IS_ARM_FIXED_SVE2)
#  define EVE_SIMD_IS_ANY_FIXED_SVE
#endif

// We successfully detected some native SIMD
#if !defined(EVE_NO_SIMD)
#  if defined(EVE_SIMD_IS_ANY_FIXED_SVE)
#    define EVE_SUPPORTS_NATIVE_SIMD
#    define EVE_INCLUDE_ARM_SVE_HEADER
#  elif defined(SPY_SIMD_IS_ARM)
#    define EVE_SUPPORTS_NATIVE_SIMD
#    define EVE_INCLUDE_ARM_NEON_HEADER
#  endif
#endif
