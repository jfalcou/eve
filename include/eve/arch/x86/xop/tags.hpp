//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_XOP_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_XOP_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for XOP SIMD implementation
  struct xop_
  {
  };

  // Runtime detection of CPU support
  inline bool is_supported(xop_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(11, 0x80000001, detail::ebx) &&
                                 detail::detect_feature(27, 0x80000001, detail::ecx);
    return detected;
#else
    return false;
#endif
  }

  // XOP extension tag object
  inline const xop_ xop = {};
}

#endif
