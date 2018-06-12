//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_TAGS_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>
#include <eve/detail/cpuid.hpp>

namespace eve
{
  // ABI tag for all X86 128 bits SIMD registers
  struct sse_ {};

  // dispatching tag for SSE2 SIMD implementation
  struct sse2_ : simd_ { using parent = simd_; };

  // Runtime detection of CPU support
  inline bool is_supported(sse2_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_feature(25, 0x00000001, detail::edx);
    return detected;
    #else
    return false;
    #endif
  }

  // SSE2 extension tag object
  inline const sse2_ sse2 = {};
}

#endif
