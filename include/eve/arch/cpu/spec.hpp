//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/spy.hpp>

#if !defined(EVE_CURRENT_ABI)
#  define EVE_CURRENT_ABI ::eve::emulated_
#  define EVE_CURRENT_API ::eve::undefined_simd_
#  define EVE_ABI_NAMESPACE cpu_abi_v0
#endif
