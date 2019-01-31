//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE3_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE3_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for SSE3 SIMD implementation
  struct sse3_ : sse2_
  {
    using parent = sse2_;
  };

  // Runtime detection of CPU support
  inline bool is_supported(sse3_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(0, 0x00000001, detail::ecx);
    return detected;
#else
    return false;
#endif
  }

  // SSE3 extension tag object
  inline const sse3_ sse3 = {};
}

#endif
