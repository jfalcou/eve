//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/x86/predef.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/spy.hpp>

namespace eve
{
  //================================================================================================
  // ABI tags for all X86 bits SIMD registers
  //================================================================================================
  template<std::size_t Size, bool Logical> struct x86_abi_
  {
    static constexpr std::size_t  bits             = Size;
    static constexpr std::size_t  bytes            = Size/8;
    static constexpr bool         is_wide_logical  = Logical;

    template<typename Type>
    static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= 16);

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = 16 / sizeof(Type);
  };

# if defined(SPY_SIMD_IS_X86_AVX512)
  struct x86_128_ : x86_abi_<128, false> {};
  struct x86_256_ : x86_abi_<256, false> {};
# else
  struct x86_128_ : x86_abi_<128, true> {};
  struct x86_256_ : x86_abi_<256, true> {};
# endif

  struct x86_512_ : x86_abi_<512, false> {};

  //================================================================================================
  // Dispatching tag for SSE* SIMD implementation
  //================================================================================================
  struct sse2_    : simd_   {};
  struct sse3_    : sse2_   {};
  struct ssse3_   : sse3_   {};
  struct sse4_1_  : ssse3_  {};
  struct sse4_2_  : sse4_1_ {};
  struct avx_     : sse4_2_ {};
  struct avx2_    : avx_    {};
  struct avx512_  : avx2_   {};

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
  // x86 ABI concept
  //================================================================================================
  template<typename T>
  concept x86_abi = detail::is_one_of<T>(detail::types<x86_128_, x86_256_, x86_512_> {});
}
