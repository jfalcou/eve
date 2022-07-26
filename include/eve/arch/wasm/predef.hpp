//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

// We successfully detected some native SIMD
#if defined(SPY_ARCH_IS_WASM) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_WASM
#  define EVE_INCLUDE_WASM_HEADER
#endif
