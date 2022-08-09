//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

// We successfully detected some native SIMD
#if defined(SPY_SIMD_IS_ARM_FIXED_SVE) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_ARM_SVE
#  define EVE_INCLUDE_SVE_HEADER
#elif defined(SPY_SIMD_IS_ARM) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_ARM
#  define EVE_INCLUDE_ARM_HEADER
#endif

#if defined(EVE_HACK_FOR_CLANG_TOOLING)
#   pragma clang diagnostic ignored "-Wmany-braces-around-scalar-init"
#   define EVE_INCLUDE_ARM_HEADER

using uint8x8_t   = int;
using uint8x8x2_t = int;

#endif
