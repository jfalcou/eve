//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Make MSVC compliant with macro we look for
#if defined(_MSC_VER)
#  if defined(EVE_ASSUME_SSE3)
#    define __SSE3__
#  endif

#  if defined(EVE_ASSUME_SSSE3)
#    define __SSSE3__
#  endif

#  if defined(EVE_ASSUME_SSE4_1)
#    define __SSE4_1__
#  endif

#  if defined(EVE_ASSUME_SSE4_2)
#    define __SSE4_2__
#  endif

#  if defined(EVE_ASSUME_FMA3)
#    define __FMA3__
#  endif
#endif

#include <eve/detail/spy.hpp>

// We successfully detected some native SIMD
#if defined(SPY_SIMD_IS_X86) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_X86
#  define EVE_INCLUDE_X86_HEADER

// Don't trigger AVX512 if we don't have at least Skylake support
#  if defined(SPY_SIMD_IS_X86_AVX512)
#   if !(   defined(__AVX512BW__) && defined(__AVX512CD__)  \
        &&  defined(__AVX512DQ__) && defined(__AVX512VL__)  \
        &&  defined(__AVX512DQ__) && defined(__AVX512VL__)  )
#    undef SPY_SIMD_IS_X86_AVX512
#    undef SPY_SIMD_DETECTED ::spy::detail::simd_version::avx512_
#    define EVE_INCOMPLETE_AVX512_SUPPORT
#    define SPY_SIMD_IS_X86_AVX2
#    define SPY_SIMD_DETECTED ::spy::detail::simd_version::avx2_
#   endif
#  endif

# if defined(EVE_INCOMPLETE_AVX512_SUPPORT) || \
     defined(SPY_SIMD_IS_X86_AVX512)        || \
     (defined(SPY_SIMD_IS_X86_AVX2) && defined(EVE_USE_BMI_ON_AVX2))
#define EVE_USE_BMI
#endif

#endif
