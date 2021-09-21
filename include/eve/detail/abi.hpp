//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

// Force a function to be inline
#if defined(EVE_NO_FORCEINLINE)
#  define EVE_FORCEINLINE inline
#else
#  if defined(_MSC_VER)
#    define EVE_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
#    define EVE_FORCEINLINE inline __attribute__((__always_inline__))
#  else
#    define EVE_FORCEINLINE inline
#  endif
#endif

// Force a lambda function to be inline
#if !defined(EVE_LAMBDA_FORCEINLINE)
#  if defined(_MSC_VER)
#    define EVE_LAMBDA_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
#    define EVE_LAMBDA_FORCEINLINE __attribute__((__always_inline__))
#  else
#    define EVE_LAMBDA_FORCEINLINE
#  endif
#endif

// Captures math related options and translate to proper setup
#if defined(__FAST_MATH__) && !defined(EVE_FAST_MATH)
#  define EVE_FAST_MATH
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_NANS)
#  define EVE_NO_NANS
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_MINUSZERO)
#  define EVE_NO_MINUSZERO
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_INFINITIES)
#  define EVE_NO_INFINITIES
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_DENORMALS)
#  define EVE_NO_DENORMALS
#endif

#if defined(EVE_NO_NANS) && defined(EVE_NO_INFINITIES) && !defined(EVE_NO_INVALIDS)
#  define EVE_NO_INVALIDS
#elif defined(EVE_NO_INVALIDS)
#  define EVE_NO_NANS
#  define EVE_NO_INFINITIES
#endif
