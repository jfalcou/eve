//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

#if !defined(EVE_CURRENT_ABI)
#  define EVE_CURRENT_ABI ::eve::emulated_
#  define EVE_CURRENT_API ::eve::cpu_
#  define EVE_STRICT_EMULATION
#  define EVE_ABI_NAMESPACE cpu_abi_v0
#endif

//==================================================================================================
// Additionnal ISA support
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
}
