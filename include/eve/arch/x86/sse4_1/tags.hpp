//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4_1_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4_1_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for SSE4.1 SIMD implementation
  struct sse4_1_ : ssse3_ { using parent = ssse3_; };

  // Runtime detection of CPU support
  inline bool is_supported(sse4_1_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(19, 0x00000001, detail::ecx);
    return detected;
    #else
    return false;
    #endif
  }

  // SSE4.1 extension tag object
  inline const sse4_1_ sse4_1 = {};
}

#endif
