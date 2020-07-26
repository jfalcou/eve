//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/x86/predef.hpp>
#include <eve/detail/cpuid.hpp>
#include <eve/detail/meta/traits.hpp>

namespace eve
{
  // clang-format off
  //================================================================================================
  // ABI tag for all X86 128 bits SIMD registers
  //================================================================================================
  struct sse_ {};

  //================================================================================================
  // Dispatching tag for SSE* SIMD implementation
  //================================================================================================
  struct sse2_    : simd_   { using parent  = simd_;  };
  struct sse3_    : sse2_   { using parent  = sse2_;  };
  struct ssse3_   : sse3_   { using parent  = sse3_;  };
  struct sse4_1_  : ssse3_  { using parent  = ssse3_; };
  struct sse4_2_  : sse4_1_ { using parent  = sse4_1_;};
  struct avx_     : sse4_2_ { using parent  = sse4_2_;};
  struct avx2_    : avx_    { using parent  = avx_;   };

  //================================================================================================
  // SSE* extension tag objects - Forwarded from SPY
  //================================================================================================
  inline constexpr auto sse2   = spy::sse2_;
  inline constexpr auto sse3   = spy::sse3_;
  inline constexpr auto ssse3  = spy::ssse3_;
  inline constexpr auto sse4_1 = spy::sse41_;
  inline constexpr auto sse4_2 = spy::sse42_;
  inline constexpr auto avx    = spy::avx_;
  inline constexpr auto avx2   = spy::avx2_;

  //================================================================================================
  // Specific ISA tags
  //================================================================================================
  struct xop_   {};
  struct fma3_  {};
  struct fma4_  {};

  inline constexpr auto xop    = xop_{};
  inline constexpr auto fma3   = fma3_{};
  inline constexpr auto fma4   = fma4_{};

  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  template<auto Version> inline bool is_supported(spy::x86_simd_info<Version> const &) noexcept
  {
          if constexpr( Version == sse2.version   ) return detail::cpuid_states.supports_sse2();
    else  if constexpr( Version == sse3.version   ) return detail::cpuid_states.supports_sse3();
    else  if constexpr( Version == ssse3.version  ) return detail::cpuid_states.supports_ssse3();
    else  if constexpr( Version == sse4_1.version ) return detail::cpuid_states.supports_sse4_1();
    else  if constexpr( Version == sse4_2.version ) return detail::cpuid_states.supports_sse4_2();
    else  if constexpr( Version == avx.version    ) return detail::cpuid_states.supports_avx();
    else  if constexpr( Version == avx2.version   ) return detail::cpuid_states.supports_avx2();
    else                                            return false;
  }

  inline bool is_supported(xop_ const &)  noexcept  { return detail::cpuid_states.supports_xop(); }
  inline bool is_supported(fma3_ const &) noexcept  { return detail::cpuid_states.supports_fma3();}
  inline bool is_supported(fma4_ const &) noexcept  { return detail::cpuid_states.supports_fma4();}

  //================================================================================================
  // x86 ABI concept
  //================================================================================================
  template<typename T>
  concept x86_abi = detail::is_one_of<T>(detail::types<sse_, avx_> {});
}

