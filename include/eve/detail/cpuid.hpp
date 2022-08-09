//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>


#if defined(SPY_ARCH_IS_AMD64)
#  if __has_include(<cpuid.h>)
#    include <cpuid.h>
#    define EVE_HAS_CPUID
#  endif

#  if __has_include(<intrin.h>) && !defined(EVE_HAS_CPUID)
#    include <intrin.h>
#  endif

#include <bitset>
#include <vector>
#include <array>

namespace
{
#  if defined(EVE_HAS_CPUID)
  using register_t = unsigned int;
#  else
  using register_t = int;
#  endif

  enum registerID { eax = 0, ebx = 1, ecx = 2, edx = 3 };

  inline void cpuid(register_t registers[ 4 ], int function) noexcept
  {
#  if defined(EVE_HAS_CPUID)
    __cpuid(function, registers[ eax ], registers[ ebx ], registers[ ecx ], registers[ edx ]);
#  else
    __cpuid(registers, function);
#  endif
  }

  inline void cpuidex(register_t registers[ 4 ], int function, int subfunction) noexcept
  {
#  if defined(EVE_HAS_CPUID)
    __cpuid_count(function,
                  subfunction,
                  registers[ eax ],
                  registers[ ebx ],
                  registers[ ecx ],
                  registers[ edx ]);
#  else
    __cpuidex(registers, function, subfunction);
#  endif
  }

  /*
    This code is an slight adaptation of:
    https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=vs-2019
  */
  struct runtime_flags
  {
    runtime_flags() : isIntel_{ false }, isAMD_{ false }
                    , f1_ECX_{ 0 }, f1_EDX_{ 0 }, f7_EBX_{ 0 },f7_ECX_{ 0 }, f81_ECX_{ 0 }
    {
      std::array<register_t, 4> cpui, cpui0, cpui1, cpui7;

      // Calling cpuid with function 0 gets the number of the highest valid extended ID.
      cpuid(cpui.data(), 0);
      cpuidex(cpui0.data(), 0, 0);
      cpuidex(cpui1.data(), 1, 0);
      cpuidex(cpui7.data(), 7, 0);

      // Compare minimal amount of vendor string
      isIntel_ = (cpui0[1] == 0x756e6547); // data == 'Genu'
      isAMD_   = (cpui0[1] == 0x68747541); // data == 'Auth'

      // load bitset with flags for function 0x00000001
      if (cpui[0] >= 1)
      {
        f1_ECX_ = cpui1[2];
        f1_EDX_ = cpui1[3];
      }

      // load bitset with flags for function 0x00000007
      if (cpui[0] >= 7)
      {
        f7_EBX_ = cpui7[1];
        f7_ECX_ = cpui7[2];
      }

      // Calling cpuid with function 0x80000000 gets the number of the highest valid extended ID.
      cpuid(cpui.data(), 0x80000000);
      if( cpui[0]>= 0x80000001)
      {
        cpuidex(cpui.data(), 0x80000001, 0);
      // load bitset with flags for function 0x80000001
      f81_ECX_ = cpui[2];
      }
    }

    bool supports_sse2()     const noexcept { return f1_EDX_[26];                 }
    bool supports_sse3()     const noexcept { return f1_ECX_[0];                  }
    bool supports_ssse3()    const noexcept { return f1_ECX_[9];                  }
    bool supports_sse4_1()   const noexcept { return f1_ECX_[19];                 }
    bool supports_sse4_2()   const noexcept { return f1_ECX_[20];                 }
    bool supports_fma3()     const noexcept { return f1_ECX_[12] && f1_ECX_[27];  }
    bool supports_avx()      const noexcept { return f1_ECX_[28] && f1_ECX_[27];  }
    bool supports_avx2()     const noexcept { return f7_EBX_[5]  && f1_ECX_[27];  }

    bool supports_avx512F()  const noexcept { return f7_EBX_[16]; }
    bool supports_avx512PF() const noexcept { return f7_EBX_[26]; }
    bool supports_avx512ER() const noexcept { return f7_EBX_[27]; }
    bool supports_avx512CD() const noexcept { return f7_EBX_[28]; }

    bool supports_sse4_a()   const noexcept { return isAMD_ && f81_ECX_[6];                  }

    bool isIntel_, isAMD_;
    std::bitset<32> f1_ECX_, f1_EDX_, f7_EBX_, f7_ECX_, f81_ECX_;
  };
}
#else
namespace
{
  struct runtime_flags
  {
    bool supports_sse2()     const noexcept { return false; }
    bool supports_sse3()     const noexcept { return false; }
    bool supports_ssse3()    const noexcept { return false; }
    bool supports_sse4_1()   const noexcept { return false; }
    bool supports_sse4_2()   const noexcept { return false; }
    bool supports_fma3()     const noexcept { return false; }
    bool supports_avx()      const noexcept { return false; }
    bool supports_avx2()     const noexcept { return false; }

    bool supports_avx512F()  const noexcept { return false; }
    bool supports_avx512PF() const noexcept { return false; }
    bool supports_avx512ER() const noexcept { return false; }
    bool supports_avx512CD() const noexcept { return false; }

    bool supports_sse4_a()   const noexcept { return false;  }
  };
}
#endif

namespace eve::detail
{
  inline const runtime_flags cpuid_states = {};
}
