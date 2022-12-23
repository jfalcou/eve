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
  template<x86_tag API>
  bool is_supported(API const& ) noexcept
  {
    using namespace detail;

          if constexpr( API::version == sse2.value()   ) return cpuid_states.supports_sse2();
    else  if constexpr( API::version == sse3.value()   ) return cpuid_states.supports_sse3();
    else  if constexpr( API::version == ssse3.value()  ) return cpuid_states.supports_ssse3();
    else  if constexpr( API::version == sse4_1.value() ) return cpuid_states.supports_sse4_1();
    else  if constexpr( API::version == sse4_2.value() ) return cpuid_states.supports_sse4_2();
    else  if constexpr( API::version == avx.value()    ) return cpuid_states.supports_avx();
    else  if constexpr( API::version == avx2.value()   ) return cpuid_states.supports_avx2();
    else  if constexpr( API::version == avx512.value() ) return cpuid_states.supports_avx512F();
    else                                                        return false;
  }

  inline bool is_supported(fma3_ const &) noexcept  { return detail::cpuid_states.supports_fma3();}
}
