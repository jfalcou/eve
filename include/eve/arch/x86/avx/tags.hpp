//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for AVX SIMD implementation
  struct avx_ : sse4_2_ { using parent = sse4_2_; };

  // Runtime detection of CPU support
  inline bool is_supported(avx_ const& ) noexcept
  {
    #if defined(EVE_ARCH_IS_X86)
    static const bool detected = detail::detect_features( (1<<28)|(1<<27)|(1<<26)
                                                        , 0x00000001, detail::ecx
                                                        );
    return detected;
    #else
    return false;
    #endif
  }

  // AVX extension tag object
  inline const avx_ avx = {};
}

#endif
