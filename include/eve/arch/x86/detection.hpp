//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
    using namespace detail;

          if constexpr( Version == sse2.value().version   ) return cpuid_states.supports_sse2();
    else  if constexpr( Version == sse3.value().version   ) return cpuid_states.supports_sse3();
    else  if constexpr( Version == ssse3.value().version  ) return cpuid_states.supports_ssse3();
    else  if constexpr( Version == sse4_1.value().version ) return cpuid_states.supports_sse4_1();
    else  if constexpr( Version == sse4_2.value().version ) return cpuid_states.supports_sse4_2();
    else  if constexpr( Version == avx.value().version    ) return cpuid_states.supports_avx();
    else  if constexpr( Version == avx2.value().version   ) return cpuid_states.supports_avx2();
    else  if constexpr( Version == avx512.value().version ) return cpuid_states.supports_avx512F();
    else                                                    return false;
  }

  inline bool is_supported(fma3_ const &) noexcept  { return detail::cpuid_states.supports_fma3();}
}
