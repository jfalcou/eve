//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#if defined(EVE_SUPPORTS_FMA3)
#  include <immintrin.h>
namespace eve
{
  inline constexpr bool supports_fma3 = true;
}
#else
namespace eve
{
  inline constexpr bool supports_fma3 = false;
}
#endif

#if defined(EVE_SUPPORTS_FMA4)
#  if defined(EVE_COMP_IS_MSVC)
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    include <fma4intrin.h>
#  endif
namespace eve
{
  inline constexpr bool supports_fma4 = true;
}
#else
namespace eve
{
  inline constexpr bool supports_fma4 = false;
}
#endif

#if defined(EVE_SUPPORTS_XOP)
#  if defined(EVE_COMP_IS_MSVC)
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    include <xopintrin.h>
#  endif
namespace eve
{
  inline constexpr bool supports_xop = true;
}
#else
namespace eve
{
  inline constexpr bool supports_xop = false;
}
#endif

#if !defined(__aarch64__)
#  ifndef EVE_NO_DENORMALS
#    define EVE_NO_DENORMALS
#  endif
namespace eve
{
  inline constexpr bool supports_aarch64 = false;
}
#else
namespace eve
{
  inline constexpr bool supports_aarch64 = true;
}
#endif

#endif
