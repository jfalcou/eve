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
#include <eve/deps/spy.hpp>

namespace eve
{
  //==================================================================================================
  // Additional ISA support
  struct x86_isa_
  {
    static constexpr bool supports_fma3               = spy::supports::fma_;
    static constexpr bool supports_avx512bw           = spy::supports::avx512::bw_;
    static constexpr bool supports_avx512cd           = spy::supports::avx512::cd_;
    static constexpr bool supports_avx512dq           = spy::supports::avx512::dq_;
    static constexpr bool supports_avx512ifma         = spy::supports::avx512::ifma_;
    static constexpr bool supports_avx512pf           = spy::supports::avx512::pf_;
    static constexpr bool supports_avx512vl           = spy::supports::avx512::vl_;
    static constexpr bool supports_avx512popcntdq_    = spy::supports::avx512::popcntdq_;
    static constexpr bool supports_avx512_4fmaps_     = spy::supports::avx512::_4fmaps_;
    static constexpr bool supports_avx512vnniw_       = spy::supports::avx512::vnniw_;
    static constexpr bool supports_avx512vbmi_        = spy::supports::avx512::vbmi_;
    static constexpr bool supports_avx512bf16_        = spy::supports::avx512::bf16_;
    static constexpr bool supports_avx512bitalg_      = spy::supports::avx512::bitalg_;
    static constexpr bool supports_avx512vbmi2_       = spy::supports::avx512::vbmi2_;
    static constexpr bool supports_avx512vnni_        = spy::supports::avx512::vnni_;
    static constexpr bool supports_avx512vpintersect_ = spy::supports::avx512::vpintersect_;
  
  #ifdef EVE_USE_BMI
    static constexpr bool supports_bmi_well = true;
  #else
    static constexpr bool supports_bmi_well = false;
  #endif
  
  #if defined(EVE_AVX512_DEFAULT_64_BYTES)
    static constexpr bool avx512_default_64_bytes = true;
  #else
    static constexpr bool avx512_default_64_bytes = false;
  #endif

  };
  //================================================================================================
  // ABI tags for all X86 bits SIMD registers
  //================================================================================================
  template<std::size_t Width, bool Logical> struct x86_abi_ : x86_isa_
  {
    static constexpr std::size_t  bits             = Width;
    static constexpr std::size_t  bytes            = Width/8;
    static constexpr bool         is_wide_logical  = Logical;
    static constexpr bool         has_defined_logical_tail = true;
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
  inline constexpr auto fma3 = fma3_{};

  //================================================================================================
  // x86 ABI concept
  //================================================================================================
  template<typename T>
  concept x86_abi = _::one_of<T, x86_128_, x86_256_, x86_512_>;

  template<typename T>
  concept x86_tag = requires(T) { typename T::is_x86; };

  namespace _
  {
    template<typename T, x86_abi ABI>
    inline constexpr bool use_complete_storage<T, ABI> = ((T::size() * sizeof(typename T::value_type)) >= 16);

    template<typename T, x86_abi ABI>
    inline constexpr width_type expected_width<T, ABI> = ABI::bytes / sizeof(T);

    template<typename T, x86_abi ABI>
    inline constexpr width_type fundamental_width<T,ABI> = 16 / sizeof(T);
  }
}
