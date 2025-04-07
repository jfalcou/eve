//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if defined(_MSC_VER)
#    if _MSVC_LANG < 202002L
#        error "Eve requires C++20 or higher. Use /std:c++20 or higher to enable C++20 features."
#    endif
#else
#    if __cplusplus < 202002L
#        error "Eve requires C++20 or higher. Use -std=c++20 or higher to enable C++20 features."
#    endif
#endif

// Faster than std::forward
#define EVE_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

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

// Assume an expression to be true at compile time
#if defined(EVE_NO_ASSUME)
#  define EVE_ASSUME(...)
#else
#  if defined(__clang__)
#    define EVE_ASSUME(...) do { __builtin_assume(__VA_ARGS__); } while(0)
#  elif defined(__GNUC__)
#    if __GNUC__ >= 13
#      define EVE_ASSUME(...) do { __attribute__((__assume__(__VA_ARGS__))); } while(0)
#    else
#      define EVE_ASSUME(...) do { if (!bool{__VA_ARGS__}) __builtin_unreachable(); } while(0)
#    endif
#  elif defined(_MSC_VER)
#    define EVE_ASSUME(...) do { __assume(__VA_ARGS__); } while(0)
#  else
#    define EVE_ASSUME(...)
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
