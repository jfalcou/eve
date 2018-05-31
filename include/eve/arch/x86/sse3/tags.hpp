//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE3_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE3_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for SSE3 SIMD implementation
  struct sse3_ : sse2_ { using parent = sse2_; };

  // Runtime detection of CPU support
  inline bool is_supported(sse3_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(0, 0x00000001, detail::ecx);
    return detected;
    #else
    return false;
    #endif
  }

  // SSE3 extension tag object
  constexpr inline sse3_ sse3 = {};
}

#endif
