//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
  template<ppc_tag API> bool is_supported(API const& ) noexcept
  {
    #if defined( SPY_SIMD_IS_PPC )
    if constexpr( API::version >= spy::vsx_ )
    {
      static const bool detected = (__builtin_cpu_supports( "vsx" ) != 0);
      return detected;
    }
    else if constexpr( API::version >= spy::vmx_ )
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
