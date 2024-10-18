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

namespace eve
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
#    define EVE_ABI_NAMESPACE arm_sve128_v0
#  elif __ARM_FEATURE_SVE_BITS == 256
#    define EVE_CURRENT_ABI   ::eve::arm_sve_256_
#    define EVE_CURRENT_API   ::eve::sve2_256_
#    define EVE_ABI_NAMESPACE arm_sve256_v0
#  elif __ARM_FEATURE_SVE_BITS == 512
#    define EVE_CURRENT_ABI   ::eve::arm_sve_512_
#    define EVE_CURRENT_API   ::eve::sve2_512_
#    define EVE_ABI_NAMESPACE arm_sve512_v0
#  endif
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE)
#  include <arm_sve.h>
#  if __ARM_FEATURE_SVE_BITS == 128
#    define EVE_CURRENT_ABI   ::eve::arm_sve_128_
#    define EVE_CURRENT_API   ::eve::sve128_
#    define EVE_ABI_NAMESPACE arm_sve128_v0
#  elif __ARM_FEATURE_SVE_BITS == 256
#    define EVE_CURRENT_ABI   ::eve::arm_sve_256_
#    define EVE_CURRENT_API   ::eve::sve256_
#    define EVE_ABI_NAMESPACE arm_sve256_v0
#  elif __ARM_FEATURE_SVE_BITS == 512
#    define EVE_CURRENT_ABI   ::eve::arm_sve_512_
#    define EVE_CURRENT_API   ::eve::sve512_
#    define EVE_ABI_NAMESPACE arm_sve512_v0
#  endif
#endif