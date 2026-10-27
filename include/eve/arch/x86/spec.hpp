//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <cstdint>
#include <cstddef>

//==================================================================================================
// X86 hardware info
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 2 * sizeof(void *);
    static constexpr std::size_t simd    = 2 * sizeof(void *);
  };
}

//==================================================================================================
// X86 SIMD API/ABI
#include <immintrin.h>

#if defined(SPY_SIMD_IS_X86_AVX512)
#  define EVE_CURRENT_ABI ::eve::x86_512_
#  if defined(EVE_INCOMPLETE_AVX512_SUPPORT)
#    define EVE_CURRENT_API ::eve::avx2_
#  else
#    define EVE_CURRENT_API ::eve::avx512_
#  endif
#  define EVE_ABI_NAMESPACE avx512_abi_v0
#elif defined(SPY_SIMD_IS_X86_AVX2)
#  define EVE_CURRENT_ABI ::eve::x86_256_
#  define EVE_CURRENT_API ::eve::avx2_
#  define EVE_ABI_NAMESPACE avx_abi_v0
#elif defined(SPY_SIMD_IS_X86_AVX)
#  define EVE_CURRENT_ABI ::eve::x86_256_
#  define EVE_CURRENT_API ::eve::avx_
#  define EVE_ABI_NAMESPACE avx_abi_v0
#elif defined(SPY_SIMD_IS_X86_SSE4_2)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse4_2_
#  define EVE_ABI_NAMESPACE sse_abi_v0
#elif defined(SPY_SIMD_IS_X86_SSE4_1)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse4_1_
#  define EVE_ABI_NAMESPACE sse_abi_v0
#elif defined(SPY_SIMD_IS_X86_SSSE3)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::ssse3_
#  define EVE_ABI_NAMESPACE sse_abi_v0
#elif defined(SPY_SIMD_IS_X86_SSE3)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse3_
#  define EVE_ABI_NAMESPACE sse_abi_v0
#elif defined(SPY_SIMD_IS_X86_SSE2)
#  define EVE_CURRENT_ABI ::eve::x86_128_
#  define EVE_CURRENT_API ::eve::sse2_
#  define EVE_ABI_NAMESPACE sse_abi_v0
#endif

//==================================================================================================
// Additional ISA support
namespace eve
{
  inline constexpr bool supports_fma3               = spy::supports::fma_;
  inline constexpr bool supports_avx512bw           = spy::supports::avx512::bw_;
  inline constexpr bool supports_avx512cd           = spy::supports::avx512::cd_;
  inline constexpr bool supports_avx512dq           = spy::supports::avx512::dq_;
  inline constexpr bool supports_avx512ifma         = spy::supports::avx512::ifma_;
  inline constexpr bool supports_avx512pf           = spy::supports::avx512::pf_;
  inline constexpr bool supports_avx512vl           = spy::supports::avx512::vl_;
  inline constexpr bool supports_avx512popcntdq_    = spy::supports::avx512::popcntdq_;
  inline constexpr bool supports_avx512_4fmaps_     = spy::supports::avx512::_4fmaps_;
  inline constexpr bool supports_avx512vnniw_       = spy::supports::avx512::vnniw_;
  inline constexpr bool supports_avx512vbmi_        = spy::supports::avx512::vbmi_;
  inline constexpr bool supports_avx512bf16_        = spy::supports::avx512::bf16_;
  inline constexpr bool supports_avx512bitalg_      = spy::supports::avx512::bitalg_;
  inline constexpr bool supports_avx512vbmi2_       = spy::supports::avx512::vbmi2_;
  inline constexpr bool supports_avx512vnni_        = spy::supports::avx512::vnni_;
  inline constexpr bool supports_avx512vpintersect_ = spy::supports::avx512::vpintersect_;

#ifdef EVE_USE_BMI
  inline constexpr bool supports_bmi_well           = true;
#else
  inline constexpr bool supports_bmi_well           = false;
#endif

}