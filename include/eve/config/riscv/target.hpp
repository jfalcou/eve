//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// We successfully detected some native SIMD
#if defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_INCLUDE_RISCV_HEADER
#endif
