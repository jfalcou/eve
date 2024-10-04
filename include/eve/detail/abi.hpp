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

// strip parenthesis from the macro argument
#define EVE_REMOVE_PARENS(x)              EVE_EVAL((EVE_REMOVE_PARENS_I x), x)
#define EVE_REMOVE_PARENS_I(...)          1, 1
#define EVE_APPLY(macro, args)            EVE_APPLY_I(macro, args)
#define EVE_APPLY_I(macro, args)          macro args
#define EVE_EVAL_I(test, x)               EVE_MAYBE_STRIP_PARENS(EVE_TEST_ARITY test, x)
#define EVE_EVAL(test, x)                 EVE_EVAL_I(test, x)
#define EVE_TEST_ARITY(...)               EVE_APPLY(EVE_TEST_ARITY_I, (__VA_ARGS__, 2, 1))
#define EVE_TEST_ARITY_I(a, b, c, ...)    c
#define EVE_MAYBE_STRIP_PARENS(cond, x)   EVE_MAYBE_STRIP_PARENS_I(cond, x)
#define EVE_MAYBE_STRIP_PARENS_I(cond, x) EVE_CAT(EVE_MAYBE_STRIP_PARENS_, cond)(x)
#define EVE_MAYBE_STRIP_PARENS_1(x)       x
#define EVE_MAYBE_STRIP_PARENS_2(x)       EVE_APPLY(EVE_MAYBE_STRIP_PARENS_2_I, x)
#define EVE_MAYBE_STRIP_PARENS_2_I(...)   __VA_ARGS__

// Concatenate two tokens
#define EVE_CAT(x, y)   EVE_CAT_I(x, y)
#define EVE_CAT_I(x, y) x##y
