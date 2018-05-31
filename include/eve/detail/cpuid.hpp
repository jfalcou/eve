//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_DETAIL_CPUID_HPP_INCLUDED
#define EVE_DETAIL_CPUID_HPP_INCLUDED

#include <eve/detail/architecture.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/os.hpp>
#include <cstdio>

#if defined(EVE_ARCH_IS_X86)

#if defined(EVE_COMP_IS_GNUC) || defined(EVE_COMP_IS_CLANG)
  #define EVE_CPUID_HEADER
#else
  #if defined(EVE__OS_IS_LINUX)
    #if defined(EVE_COMP_IS_INTEL) || defined(EVE_COMP_IS_INTEL_EMULATED)
      #define EVE_CPUID_HEADER
    #endif
  #endif
#endif

#if defined(EVE_CPUID_HEADER)
#include <cpuid.h>
#else
#include <intrin.h>
#endif

namespace eve { namespace detail
{
#if defined(EVE_CPUID_HEADER)
  using register_t = unsigned int;
#else
  using register_t = int;
#endif

  enum registerID { eax=0, ebx=1, ecx=2, edx=3 };

  inline void cpuid(register_t registers[4], int function) noexcept
  {
#if defined(EVE_CPUID_HEADER)
    __cpuid (function, registers[eax], registers[ebx], registers[ecx], registers[edx]);
#else
    __cpuid(registers, function);
#endif
  }

  inline void cpuidex(register_t registers[4], int function, int subfunction) noexcept
  {
#if defined(EVE_CPUID_HEADER)
    __cpuid_count ( function, subfunction
                  , registers[eax], registers[ebx], registers[ecx], registers[edx]
                  );
#else
    __cpuidex(registers, function, subfunction);
#endif
  }

  inline bool detect_feature(int bit, int function, int register_id) noexcept
  {
    register_t regs_x86[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    cpuidex(regs_x86, function, 0);
    return (regs_x86[register_id] & (1 << bit)) != 0;
  }

  inline bool detect_features(int bits, int function, int register_id) noexcept
  {
    register_t regs_x86[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
    cpuidex(regs_x86, function, 0);
    return (regs_x86[register_id] & bits) != 0;
  }
} }
#endif

#endif
