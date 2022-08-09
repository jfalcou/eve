//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/tags.hpp>
#include <eve/arch/arm/neon/tags.hpp>

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
