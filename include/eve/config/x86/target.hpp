//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// We successfully detected some native SIMD
#if defined(SPY_SIMD_IS_X86) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_INCLUDE_X86_HEADER

// Don't trigger AVX512 if we don't have at least Skylake support
#  if defined(SPY_SIMD_IS_X86_AVX512)
#   if !(   defined(SPY_SIMD_IS_X86_AVX512_BW) && defined(SPY_SIMD_IS_X86_AVX512_CD)  \
        &&  defined(SPY_SIMD_IS_X86_AVX512_DQ) && defined(SPY_SIMD_IS_X86_AVX512_VL)  )
#    undef SPY_SIMD_IS_X86_AVX512
#    undef SPY_SIMD_DETECTED
#    define EVE_INCOMPLETE_AVX512_SUPPORT
#    define SPY_SIMD_IS_X86_AVX2
#    define SPY_SIMD_DETECTED ::spy::_::simd_version::avx2_
#   endif
#  endif

# if defined(EVE_INCOMPLETE_AVX512_SUPPORT) || \
     defined(SPY_SIMD_IS_X86_AVX512)        || \
     (defined(SPY_SIMD_IS_X86_AVX2) && defined(EVE_USE_BMI_ON_AVX2))
#define EVE_USE_BMI
#endif

#endif
