//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_SPEC_HPP_INCLUDED
#define EVE_ARCH_CPU_SPEC_HPP_INCLUDED

#if !defined(EVE_CURRENT_ABI)
#  define EVE_CURRENT_ABI ::eve::emulated_
#  define EVE_CURRENT_API ::eve::cpu_
#  define EVE_STRICT_EMULATION
#endif

//==================================================================================================
// Additionnal ISA support
namespace eve
{
  inline constexpr bool supports_fma3     = spy::supports::fma_;
  inline constexpr bool supports_fma4     = spy::supports::fma4_;
  inline constexpr bool supports_xop      = spy::supports::xop_;
  inline constexpr bool supports_aarch64  = spy::supports::aarch64_;
}

#endif
