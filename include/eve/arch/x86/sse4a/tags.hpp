//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4A_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4A_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for SSE4A SIMD implementation
  struct sse4a_ {};

  // Runtime detection of CPU support
  inline bool is_supported(sse4a_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(6, 0x80000001, detail::ecx);
    return detected;
    #else
    return false;
    #endif
  }

  // SSE4A extension tag object
  constexpr inline sse4a_ sse4a = {};
}

#endif
