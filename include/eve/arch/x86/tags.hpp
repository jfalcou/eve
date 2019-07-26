//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_TAGS_HPP_INCLUDED
#define EVE_ARCH_X86_TAGS_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>
#include <eve/detail/cpuid.hpp>

namespace eve
{
  // ABI tag for all X86 128 bits SIMD registers
  struct sse_ {};

  // dispatching tag for SSE* SIMD implementation
  struct sse2_    : simd_   { using parent = simd_;   };
  struct sse3_    : sse2_   { using parent = sse2_;   };
  struct ssse3_   : sse3_   { using parent = sse3_;   };
  struct sse4_1_  : ssse3_  { using parent = ssse3_;  };
  struct sse4_2_  : sse4_1_ { using parent = sse4_1_; };
  struct avx_     : sse4_2_ { using parent = sse4_2_; };
  struct avx2_    : avx_    { using parent = avx_;    };

  // Specific ISA tags
  struct xop_   {};
  struct fma3_  {};
  struct fma4_  {};

  // SSE* extension tag objects
  inline const sse2_    sse2    = {};
  inline const sse3_    sse3    = {};
  inline const ssse3_   ssse3   = {};
  inline const sse4_1_  sse4_1  = {};
  inline const sse4_2_  sse4_2  = {};
  inline const avx_     avx     = {};
  inline const avx2_    avx2    = {};
  inline const xop_     xop     = {};
  inline const fma3_    fma3    = {};
  inline const fma4_    fma4    = {};

  // Runtime detection of CPU support

#if defined(EVE_ARCH_IS_X86)
  inline bool is_supported(sse2_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(25, 0x00000001, detail::edx);
    return detected;
  }

  inline bool is_supported(sse3_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(0, 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(ssse3_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(9, 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(sse4_1_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(19, 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(sse4_2_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(20, 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(avx_ const &) noexcept
  {
    static const bool detected =
        detail::detect_features((1 << 28) | (1 << 27) | (1 << 26), 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(avx2_ const &) noexcept
  {
    static const bool detected =
        detail::detect_features((1 << 28) | (1 << 27) | (1 << 26), 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(xop_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(11, 0x80000001, detail::ebx) &&
                                 detail::detect_feature(27, 0x80000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(fma3_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(12, 0x00000001, detail::ecx) &&
                                 detail::detect_feature(27, 0x00000001, detail::ecx);
    return detected;
  }

  inline bool is_supported(fma4_ const &) noexcept
  {
    static const bool detected = detail::detect_feature(16, 0x80000001, detail::ecx) &&
                                 detail::detect_feature(27, 0x80000001, detail::ecx);
    return detected;
  }

#else

  inline bool is_supported(sse2_    const &) noexcept { return false; }
  inline bool is_supported(sse3_    const &) noexcept { return false; }
  inline bool is_supported(ssse3_   const &) noexcept { return false; }
  inline bool is_supported(sse4_1_  const &) noexcept { return false; }
  inline bool is_supported(sse4_2_  const &) noexcept { return false; }
  inline bool is_supported(avx_     const &) noexcept { return false; }
  inline bool is_supported(avx2_    const &) noexcept { return false; }
  inline bool is_supported(xop_     const &) noexcept { return false; }
  inline bool is_supported(fma3_    const &) noexcept { return false; }
  inline bool is_supported(fma4_    const &) noexcept { return false; }

#endif
}

#endif
