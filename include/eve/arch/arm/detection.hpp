//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/tags.hpp>
#include <eve/arch/arm/neon/tags.hpp>

#if defined( SPY_SIMD_IS_ARM )
  #if defined(SPY_OS_IS_MACOS)
    #include <sys/types.h>
    #include <sys/sysctl.h>
  #elif defined( SPY_OS_IS_LINUX )
    #include <asm/hwcap.h>
    #include <sys/auxv.h>
  #endif
#endif

namespace eve
{
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  inline bool is_supported(neon128_ const &) noexcept
  {
#if defined( SPY_SIMD_IS_ARM )
# if defined(SPY_OS_IS_MACOS)
    int         val = 0;
    std::size_t len = sizeof(val);
    return sysctlbyname("hw.optional.AdvSIMD", &val, &len, nullptr, 0) == 0 && val != 0;
# else
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & (1 << 12)) != 0;
# endif
#else
    return false;
# endif
  }

  inline bool is_supported(asimd_ const &) noexcept
  {
#if defined( SPY_SIMD_IS_ARM_ASIMD )
# if defined(SPY_OS_IS_MACOS)
    int         val = 0;
    std::size_t len = sizeof(val);
    return sysctlbyname("hw.optional.AdvSIMD", &val, &len, nullptr, 0) == 0 && val != 0;
# else
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & HWCAP_ASIMD) != 0;
# endif
#else
    return false;
 #endif
  }

}
