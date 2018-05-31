//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_XOP_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_XOP_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for XOP SIMD implementation
  struct xop_ {};

  // Runtime detection of CPU support
  inline bool is_supported(xop_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected  =   detail::detect_feature(11, 0x80000001, detail::ebx)
                                &&  detail::detect_feature(27, 0x80000001, detail::ecx);
    return detected;
    #else
    return false;
    #endif
  }

  // XOP extension tag object
  constexpr inline xop_ xop = {};
}

#endif
