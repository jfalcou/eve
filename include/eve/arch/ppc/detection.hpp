//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/tags.hpp>

namespace eve
{
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  template<auto Version> inline bool is_supported(spy::ppc_simd_info<Version> const &) noexcept
  {
    #if defined( SPY_SIMD_IS_PPC )
    if constexpr( Version >= spy::vsx_.version )
    {
      static const bool detected = (__builtin_cpu_supports( "vsx" ) != 0);
      return detected;
    }
    else if constexpr( Version >= spy::vmx_.version )
    {
      static const bool detected = (__builtin_cpu_supports( "altivec" ) != 0);
      return detected;
    }
    else
    {
      return false;
    }
    #else
      return false;
    #endif
  }
}
