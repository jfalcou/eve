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
#if defined(SPY_SIMD_IS_PPC) && !defined(EVE_NO_SIMD)
#  define EVE_SUPPORTS_NATIVE_SIMD
#  define EVE_HW_POWERPC
#  define EVE_INCLUDE_POWERPC_HEADER
#endif
