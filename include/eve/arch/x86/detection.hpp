//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/tags.hpp>
#include <eve/detail/cpuid.hpp>
#include <eve/detail/spy.hpp>

namespace eve
{
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  template<auto Version> inline bool is_supported(spy::x86_simd_info<Version> const &) noexcept
  {
          if constexpr( Version == sse2.version   ) return detail::cpuid_states.supports_sse2();
    else  if constexpr( Version == sse3.version   ) return detail::cpuid_states.supports_sse3();
    else  if constexpr( Version == ssse3.version  ) return detail::cpuid_states.supports_ssse3();
    else  if constexpr( Version == sse4_1.version ) return detail::cpuid_states.supports_sse4_1();
    else  if constexpr( Version == sse4_2.version ) return detail::cpuid_states.supports_sse4_2();
    else  if constexpr( Version == avx.version    ) return detail::cpuid_states.supports_avx();
    else  if constexpr( Version == avx2.version   ) return detail::cpuid_states.supports_avx2();
    else  if constexpr( Version == avx512.version ) return detail::cpuid_states.supports_avx512F();
    else                                            return false;
  }

  inline bool is_supported(fma3_ const &) noexcept  { return detail::cpuid_states.supports_fma3();}
}
