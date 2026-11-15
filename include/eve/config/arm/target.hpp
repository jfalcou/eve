//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(SPY_SIMD_IS_ARM_FIXED_SVE) || defined(SPY_SIMD_IS_ARM_FIXED_SVE2)
#  if __ARM_FEATURE_SVE_BITS == 128 || __ARM_FEATURE_SVE_BITS == 256 || __ARM_FEATURE_SVE_BITS == 512
#    define EVE_SIMD_IS_ANY_FIXED_SVE
#  endif
#endif

// SPY only reports NEON when there is no SVE: SVE that EVE doesn't support falls back to NEON
#if defined(SPY_SIMD_IS_ARM_ASIMD)
#  define EVE_SIMD_IS_ARM_ASIMD
#elif defined(SPY_SIMD_IS_ARM_NEON)
#  define EVE_SIMD_IS_ARM_NEON
#elif (defined(SPY_SIMD_IS_ARM_SVE) || defined(SPY_SIMD_IS_ARM_SVE2)) && !defined(EVE_SIMD_IS_ANY_FIXED_SVE) \
    && defined(__ARM_NEON)
#  define EVE_SIMD_IS_ARM_ASIMD
#endif

// We successfully detected some native SIMD
#if !defined(EVE_NO_SIMD)
#  if defined(EVE_SIMD_IS_ANY_FIXED_SVE)
#    define EVE_SUPPORTS_NATIVE_SIMD
#    define EVE_INCLUDE_ARM_SVE_HEADER
#  elif defined(EVE_SIMD_IS_ARM_ASIMD) || defined(EVE_SIMD_IS_ARM_NEON)
#    define EVE_SUPPORTS_NATIVE_SIMD
#    define EVE_INCLUDE_ARM_NEON_HEADER
#  endif
#  if defined(EVE_SIMD_IS_ARM_NEON) && !defined(EVE_NO_DENORMALS)
#    define EVE_NO_DENORMALS
#  endif
#endif
