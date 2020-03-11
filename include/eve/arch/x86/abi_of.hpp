//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_X86_ABI_OF_HPP_INCLUDED

#include <eve/arch/x86/predef.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve
{
  struct sse_;
  struct avx_;
}

namespace eve::ext
{
#if EVE_HW_X86 >= EVE_SSE2_VERSION
  template<int N>
  struct abi_of<double, N, std::enable_if_t<(N <= 2)>>
  {
    using type = ::eve::sse_;
  };

  template<int N>
  struct abi_of<float, N, std::enable_if_t<(N <= 4)>>
  {
    using type = ::eve::sse_;
  };

  template<typename T, int N>
  struct abi_of<T, N, std::enable_if_t<std::is_integral_v<T> && (N <= 16 / sizeof(T))>>
  {
    using type = ::eve::sse_;
  };
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
  template<>
  struct abi_of<double, 4>
  {
    using type = ::eve::avx_;
  };
  template<>
  struct abi_of<float, 8>
  {
    using type = ::eve::avx_;
  };

  template<typename T, int N>
  struct abi_of<T, N, std::enable_if_t<std::is_integral_v<T> && (N == 32 / sizeof(T))>>
  {
    using type = ::eve::avx_;
  };
#endif

}

#endif
