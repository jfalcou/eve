//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_ABI_OF_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve::ext
{
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
}

#endif
