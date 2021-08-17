//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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

#include <eve/detail/spy.hpp>

// We successfully detected some native SIMD
#if defined(SPY_SIMD_IS_X86) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_X86
#  define EVE_INCLUDE_X86_HEADER
#endif
