//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ABI_HPP_INCLUDED
#define EVE_DETAIL_ABI_HPP_INCLUDED

// Force a function to be inline
#if !defined(EVE_FORCEINLINE)
#  if defined(_MSC_VER)
#    define EVE_FORCEINLINE __forceinline
#  elif defined(__GNUC__) && __GNUC__ > 3
#    define EVE_FORCEINLINE inline __attribute__ ((__always_inline__))
#  else
#    define EVE_FORCEINLINE inline
#  endif
#endif

// Less sever forceinline so MSVC doesn't die
#if defined(_MSC_VER)
#define EVE_MAYBE_FORCEINLINE inline
#else
#define EVE_MAYBE_FORCEINLINE EVE_FORCEINLINE
#endif

// Captures math related options and translate to proper setup
#if defined(__FAST_MATH__) && !defined(EVE_FAST_MATH)
  #define EVE_FAST_MATH
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_NANS)
  #define EVE_NO_NANS
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_MINUSZERO)
  #define EVE_NO_MINUSZERO
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_INFINITIES)
  #define EVE_NO_INFINITIES
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_DENORMALS)
  #define EVE_NO_DENORMALS
#endif

#if defined(EVE_NO_NANS) && defined(EVE_NO_INFINITIES) && !defined(EVE_NO_INVALIDS)
  #define EVE_NO_INVALIDS
#elif defined(EVE_NO_INVALIDS)
  #define EVE_NO_NANS
  #define EVE_NO_INFINITIES
#endif

#endif
