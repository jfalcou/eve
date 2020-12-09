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
#include <eve/detail/meta.hpp>

namespace eve
{
  namespace detail
  {
# if defined(SPY_SIMD_IS_X86_AVX512)
    static inline constexpr bool x86_logical_status = false;
# else
    static inline constexpr bool x86_logical_status = true;
# endif
  }

  // clang-format off
  //================================================================================================
  // ABI tags for all X86 bits SIMD registers
  //================================================================================================
  template<std::size_t Size, bool Logical> struct x86_abi_
  {
    static constexpr std::size_t bits           = Size;
    static constexpr std::size_t bytes          = Size/8;
    static constexpr bool        is_bit_logical = Logical;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  struct x86_128_ : x86_abi_<128, true> {};
  struct x86_256_ : x86_abi_<256, true> {};
  struct x86_512_ : x86_abi_<512, true> {};

  //================================================================================================
  // Dispatching tag for SSE* SIMD implementation
  //================================================================================================
  struct sse2_    : simd_   {};
  struct sse3_    : sse2_   {};
  struct ssse3_   : sse3_   {};
  struct sse4_1_  : ssse3_  {};
  struct sse4_2_  : sse4_1_ {};

  struct avx_     : sse4_2_
  {
    static constexpr std::size_t bits           = 256;
    static constexpr std::size_t bytes          = 32;
    static constexpr bool        is_bit_logical = detail::x86_logical_status;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  struct avx2_    : avx_ {};

  struct avx512_  : avx2_
  {
    static constexpr std::size_t bits               = 512;
    static constexpr std::size_t bytes              = 64;
    static constexpr bool        is_bitwise_logical = detail::x86_logical_status;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

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
  inline constexpr auto avx512 = spy::avx512_;

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
    else  if constexpr( Version == avx512.version ) return detail::cpuid_states.supports_avx512F();
    else                                            return false;
  }

  inline bool is_supported(xop_ const &)  noexcept  { return detail::cpuid_states.supports_xop(); }
  inline bool is_supported(fma3_ const &) noexcept  { return detail::cpuid_states.supports_fma3();}
  inline bool is_supported(fma4_ const &) noexcept  { return detail::cpuid_states.supports_fma4();}

  //================================================================================================
  // x86 ABI concept
  //================================================================================================
  template<typename T>
  concept x86_abi = detail::is_one_of<T>(detail::types<x86_128_, x86_256_, x86_512_> {});
}