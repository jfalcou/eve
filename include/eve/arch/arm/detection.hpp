//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/arm/tags.hpp>

#if defined( SPY_SIMD_IS_ARM )
  #if defined( SPY_OS_IS_LINUX )
    #include <asm/hwcap.h>
    #include <sys/auxv.h>
  #endif
#endif

namespace eve
{
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  inline bool is_supported(spy::arm_simd_info<spy::detail::simd_version::neon_ > const &) noexcept
  {
    #if defined( SPY_SIMD_IS_ARM )
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & (1 << 12)) != 0;
    #else
      return false;
    #endif
  }

  inline bool is_supported(spy::arm_simd_info<spy::detail::simd_version::asimd_ > const &) noexcept
  {
    #if defined( SPY_SIMD_IS_ARM_ASIMD )
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & HWCAP_ASIMD) != 0;
    #else
      return false;
    #endif
  }
}
