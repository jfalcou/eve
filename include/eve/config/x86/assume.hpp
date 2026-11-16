//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// MSVC doesn't define the macros SPY looks for below AVX: they have to be there before SPY is included
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
#  if defined(EVE_ASSUME_SSE3) && !defined(__SSE3__)
#    define __SSE3__
#  endif

#  if defined(EVE_ASSUME_SSSE3) && !defined(__SSSE3__)
#    define __SSSE3__
#  endif

#  if defined(EVE_ASSUME_SSE4_1) && !defined(__SSE4_1__)
#    define __SSE4_1__
#  endif

#  if defined(EVE_ASSUME_SSE4_2) && !defined(__SSE4_2__)
#    define __SSE4_2__
#  endif

#  if defined(EVE_ASSUME_FMA3) && !defined(__FMA__)
#    define __FMA__
#  endif
#endif
