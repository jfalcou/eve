//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_CPUID_HPP_INCLUDED
#define EVE_DETAIL_CPUID_HPP_INCLUDED

#include <eve/detail/architecture.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/os.hpp>
#include <cstdio>

#if defined(EVE_ARCH_IS_X86)
#if __has_include(<cpuid.h>)
#include <cpuid.h>
#define EVE_HAS_CPUID
#endif

#if __has_include(<intrin.h>) && !defined(EVE_HAS_CPUID)
#include <intrin.h>
#endif

namespace eve::detail
{
#if defined(EVE_HAS_CPUID)
  using register_t = unsigned int;
#else
  using register_t = int;
#endif

  enum registerID { eax=0, ebx=1, ecx=2, edx=3 };

  inline void cpuid(register_t registers[4], int function) noexcept
  {
#if defined(EVE_HAS_CPUID)
    __cpuid (function, registers[eax], registers[ebx], registers[ecx], registers[edx]);
#else
    __cpuid(registers, function);
#endif
  }

  inline void cpuidex(register_t registers[4], int function, int subfunction) noexcept
  {
#if defined(EVE_HAS_CPUID)
    __cpuid_count ( function, subfunction
                  , registers[eax], registers[ebx], registers[ecx], registers[edx]
                  );
#else
    __cpuidex(registers, function, subfunction);
#endif
  }

  inline bool detect_features(int bits, int function, int register_id) noexcept
  {
    register_t regs_x86[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    cpuidex(regs_x86, function, 0);
    return (regs_x86[register_id] & bits) != 0;
  }

  inline bool detect_feature(int bit, int function, int register_id) noexcept
  {
    return detect_features((1 << bit),function,register_id);
  }
}
#endif

#endif
