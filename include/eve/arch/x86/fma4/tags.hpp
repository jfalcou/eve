//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_FMA4_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_FMA4_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for FMA4 SIMD implementation
  struct fma4_
  {
  };

  // Runtime detection of CPU support
  inline bool is_supported(fma4_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(16, 0x80000001, detail::ecx) &&
                                 detail::detect_feature(27, 0x80000001, detail::ecx);
    return detected;
#else
    return false;
#endif
  }

  // FMA4 extension tag object
  inline const fma4_ fma4 = {};
}

#endif
