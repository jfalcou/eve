//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/config/target.hpp>

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

#if defined(SPY_SIMD_SUPPORTS_FMA) || defined(__ARM_FEATURE_FMA) || defined(SPY_SIMD_IS_PPC_VSX) || defined(__riscv_f)
#  define EVE_HAS_HARDWARE_FMA
#endif

#if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(EVE_NO_NATIVE_FP16) && !defined(SPY_COMPILER_IS_MSVC) \
    && !defined(SPY_COMPILER_IS_CLANGCL)
#  define EVE_NATIVE_FP16
#endif

#if defined(NDEBUG) && !defined(EVE_DISABLE_ASSERTS)
#  define EVE_DISABLE_ASSERTS
#endif
