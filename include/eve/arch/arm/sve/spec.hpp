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
// SVE SIMD ABI
//==================================================================================================
#if defined(SPY_SIMD_IS_ARM_FIXED_SVE2)
#  include <arm_sve.h>
#  if __ARM_FEATURE_SVE_BITS == 128
#    define EVE_CURRENT_ABI   ::eve::arm_sve_128_
#    define EVE_CURRENT_API   ::eve::sve2_128_
#  elif __ARM_FEATURE_SVE_BITS == 256
#    define EVE_CURRENT_ABI   ::eve::arm_sve_256_
#    define EVE_CURRENT_API   ::eve::sve2_256_
#  elif __ARM_FEATURE_SVE_BITS == 512
#    define EVE_CURRENT_ABI   ::eve::arm_sve_512_
#    define EVE_CURRENT_API   ::eve::sve2_512_
#  endif
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE)
#  include <arm_sve.h>
#  if __ARM_FEATURE_SVE_BITS == 128
#    define EVE_CURRENT_ABI   ::eve::arm_sve_128_
#    define EVE_CURRENT_API   ::eve::sve128_
#  elif __ARM_FEATURE_SVE_BITS == 256
#    define EVE_CURRENT_ABI   ::eve::arm_sve_256_
#    define EVE_CURRENT_API   ::eve::sve256_
#  elif __ARM_FEATURE_SVE_BITS == 512
#    define EVE_CURRENT_ABI   ::eve::arm_sve_512_
#    define EVE_CURRENT_API   ::eve::sve512_
#  endif
#endif
