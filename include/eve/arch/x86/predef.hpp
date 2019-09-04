//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_PREDEF_HPP_INCLUDED
#define EVE_ARCH_X86_PREDEF_HPP_INCLUDED

// SSEx version numbering
#define EVE_SSE2_VERSION 2000
#define EVE_SSE3_VERSION 3000
#define EVE_SSSE3_VERSION 3100
#define EVE_SSE4_1_VERSION 4100
#define EVE_SSE4_2_VERSION 4200
#define EVE_AVX_VERSION 5000
#define EVE_AVX2_VERSION 5300

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

#  if defined(EVE_ASSUME_XOP)
#    define __XOP__
#  endif

#  if defined(EVE_ASSUME_FMA4)
#    define __FMA4__
#  endif

#  if defined(EVE_ASSUME_FMA3)
#    define __FMA3__
#  endif
#endif

// Detect current highest SSEx variant
#undef EVE_HW_X86

#if !defined(EVE_HW_X86) && defined(__AVX2__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_AVX2_VERSION
#endif

#if !defined(EVE_HW_X86) && defined(__AVX__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_AVX_VERSION
#endif

#if !defined(EVE_HW_X86) && defined(__SSE4_2__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_SSE4_2_VERSION
#endif

#if !defined(EVE_HW_X86) && defined(__SSE4_1__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_SSE4_1_VERSION
#endif

#if !defined(EVE_HW_X86) && defined(__SSSE3__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_SSSE3_VERSION
#endif

#if !defined(EVE_HW_X86) && defined(__SSE3__) && !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_SSE3_VERSION
#endif

#if !defined(EVE_HW_X86) &&                                                                        \
    (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)) &&          \
    !defined(EVE_NO_SIMD)
#  define EVE_HW_X86 EVE_SSE2_VERSION
#endif

// Detect any supplemental variants
#if defined(__FMA__)
#  define EVE_SUPPORTS_FMA3
#endif

#if defined(__FMA4__)
#  define EVE_SUPPORTS_FMA4
#endif

#if defined(__XOP__)
#  define EVE_SUPPORTS_XOP
#endif

// We successfully detected some native SIMD
#if defined(EVE_HW_X86)
#  define EVE_SUPPORTS_NATIVE_SIMD
#endif

#endif
