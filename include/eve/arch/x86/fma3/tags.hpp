//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_FMA3_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_FMA3_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for FMA3 SIMD implementation
  struct fma3_
  {
  };

  // Runtime detection of CPU support
  inline bool is_supported(fma3_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(12, 0x00000001, detail::ecx) &&
                                 detail::detect_feature(27, 0x00000001, detail::ecx);
    return detected;
#else
    return false;
#endif
  }

  // FMA4 extension tag object
  inline const fma3_ fma3 = {};
}

#endif
