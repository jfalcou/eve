//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4_2_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4_2_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for SSE4.2 SIMD implementation
  struct sse4_2_ : sse4_1_ { using parent = sse4_1_; };

  // Runtime detection of CPU support
  inline bool is_supported(sse4_2_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(20, 0x00000001, detail::ecx);
    return detected;
    #else
    return false;
    #endif
  }

  // SSE4.2 extension tag object
  inline const sse4_2_ sse4_2 = {};
}

#endif
