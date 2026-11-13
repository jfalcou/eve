//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>

#include <cstddef>

//==================================================================================================
// Register count
//==================================================================================================

EVE_NAMESPACE
{
struct register_count
{
  static constexpr std::size_t general = 32;
  static constexpr std::size_t simd    = 32;
};
}

//==================================================================================================
// NEON SIMD ABI
//==================================================================================================
#include <arm_neon.h>

#if defined(SPY_SIMD_IS_ARM_ASIMD)
#  define EVE_CURRENT_ABI   ::eve::arm_128_
#  define EVE_CURRENT_API   ::eve::asimd_
#elif defined(SPY_SIMD_IS_ARM_NEON)
#  define EVE_CURRENT_ABI   ::eve::arm_128_
#  define EVE_CURRENT_API   ::eve::neon128_
#endif

