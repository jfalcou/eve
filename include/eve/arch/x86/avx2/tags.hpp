//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX2_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_AVX2_TAGS_HPP_INCLUDED

#include <eve/detail/cpuid.hpp>

namespace eve
{
  // dispatching tag for AVX2 SIMD implementation
  struct avx2_ : avx_ { using parent = avx_; };

  // Runtime detection of CPU support
  inline bool is_supported(avx2_ const& ) noexcept
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

  // AVX2 extension tag object
  constexpr inline avx2_ avx2 = {};
}

#endif
