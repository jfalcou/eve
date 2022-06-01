//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <cstddef>

//==================================================================================================
// Register count
#if defined(EVE_HW_ARM) || defined(EVE_HW_ARM_SVE)

namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 32;
    static constexpr std::size_t simd    = 32;
  };
}

//==================================================================================================
// NEON SIMD ABI
# if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_ARM_FIXED_SVE)
#  include <arm_sve.h>
#  include <arm_neon.h>
#  if !defined(EVE_CURRENT_ABI) && (__ARM_FEATURE_SVE_BITS == 128)
#   define EVE_CURRENT_ABI ::eve::arm_sve_128_
#   define EVE_CURRENT_API ::eve::sve128_
#   define EVE_ABI_NAMESPACE arm_sve128_v0
#   define EVE_ABI_DETECTED
#elif !defined(EVE_CURRENT_ABI) && (__ARM_FEATURE_SVE_BITS == 256)
#   define EVE_CURRENT_ABI ::eve::arm_sve_256_
#   define EVE_CURRENT_API ::eve::sve256_
#   define EVE_ABI_NAMESPACE arm_sve256_v0
#   define EVE_ABI_DETECTED
#elif !defined(EVE_CURRENT_ABI) && (__ARM_FEATURE_SVE_BITS == 512)
#   define EVE_CURRENT_ABI ::eve::arm_sve_512_
#   define EVE_CURRENT_API ::eve::sve512_
#   define EVE_ABI_NAMESPACE arm_sve512_v0
#   define EVE_ABI_DETECTED
#  endif
#elif !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_ARM)
#  include <arm_neon.h>
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_ARM_ASIMD)
#   define EVE_CURRENT_ABI ::eve::arm_128_
#   define EVE_CURRENT_API ::eve::asimd_
#   define EVE_ABI_NAMESPACE arm_abi_v0
#   define EVE_ABI_DETECTED
#  endif
#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_ARM_NEON)
#   define EVE_CURRENT_ABI ::eve::arm_128_
#   define EVE_CURRENT_API ::eve::neon128_
#   define EVE_ABI_NAMESPACE arm_abi_v0
#   define EVE_ABI_DETECTED
#  endif
# endif

# if !defined(__aarch64__)
#  ifndef EVE_NO_DENORMALS
#   define EVE_NO_DENORMALS
#  endif
# endif

#endif
