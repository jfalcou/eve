//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  struct sse2_    : simd_api<simd_   , spy::sse2_>    { using is_x86 = void; };
  struct sse3_    : simd_api<sse2_   , spy::sse3_>    { using is_x86 = void; };
  struct ssse3_   : simd_api<sse3_   , spy::ssse3_>   { using is_x86 = void; };
  struct sse4_1_  : simd_api<ssse3_  , spy::sse41_>   { using is_x86 = void; };
  struct sse4_2_  : simd_api<sse4_1_ , spy::sse42_>   { using is_x86 = void; };
  struct avx_     : simd_api<sse4_2_ , spy::avx_>     { using is_x86 = void; };
  struct avx2_    : simd_api<avx_    , spy::avx2_>    { using is_x86 = void; };
  struct avx512_  : simd_api<avx2_   , spy::avx512_>  { using is_x86 = void; };

  //================================================================================================
  // SSE* extension tag objects - Forwarded from SPY
  //================================================================================================
  inline constexpr sse2_   sse2   = {};
  inline constexpr sse3_   sse3   = {};
  inline constexpr ssse3_  ssse3  = {};
  inline constexpr sse4_1_ sse4_1 = {};
  inline constexpr sse4_2_ sse4_2 = {};
  inline constexpr avx_    avx    = {};
  inline constexpr avx2_   avx2   = {};
  inline constexpr avx512_ avx512 = {};

  //================================================================================================
  // Specific ISA tags
  //================================================================================================
  struct fma3_  {};
  inline constexpr auto fma3   = fma3_{};

  //================================================================================================
  // x86 ABI concept
  //================================================================================================
  template<typename T>
  concept x86_abi = detail::is_one_of<T>(detail::types<x86_128_, x86_256_, x86_512_> {});

  template<typename T>
  concept x86_tag = requires(T) { typename T::is_x86; };
}
