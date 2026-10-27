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

//==================================================================================================
// Additional ISA support
namespace eve
{
  // Where the vector fma fuses, the scalar one has to as well: a wide and a scalar route of the
  // same call would round differently.
#if defined(__FMA__) || defined(__ARM_FEATURE_FMA) || defined(__VSX__) || defined(__riscv_f)
  inline constexpr bool supports_hardware_fma       = true;
#else
  inline constexpr bool supports_hardware_fma       = false;
#endif
}
