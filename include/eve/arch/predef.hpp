//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/spy.hpp>

#include <eve/arch/arm/predef.hpp>
#include <eve/arch/x86/predef.hpp>
#include <eve/arch/ppc/predef.hpp>
#include <eve/arch/riscv/predef.hpp>

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

#if defined(SPY_SIMD_SUPPORTS_FMA) || defined(__ARM_FEATURE_FMA) || defined(__VSX__) || defined(__riscv_f)
#  define EVE_HAS_HARDWARE_FMA
#endif

#if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(EVE_NO_NATIVE_FP16) && !defined(_MSC_VER)
#  define EVE_NATIVE_FP16
#endif

#include <eve/arch/abi_namespace.hpp>
