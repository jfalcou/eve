//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_ARM_ABI_OF_HPP_INCLUDED

#include <eve/arch/arm/predef.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve
{
  struct neon64_;
  struct neon128_;
}

namespace eve::ext
{
#if EVE_HW_ARM >= EVE_NEON_VERSION
#  if defined(__aarch64__)
  template<int N>
  struct abi_of<double, N, std::enable_if_t<(N == 2)>>
  {
    using type = neon128_;
  };
  template<int N>
  struct abi_of<double, N, std::enable_if_t<(N == 1)>>
  {
    using type = neon64_;
  };
#  endif

  template<int N>
  struct abi_of<float, N, std::enable_if_t<(N == 4)>>
  {
    using type = neon128_;
  };

  template<typename T, int N>
  struct abi_of<T, N, std::enable_if_t<std::is_integral_v<T> && (N == 16 / sizeof(T))>>
  {
    using type = neon128_;
  };

  template<int N>
  struct abi_of<float, N, std::enable_if_t<(N <= 2)>>
  {
    using type = neon64_;
  };

  template<typename T, int N>
  struct abi_of<T, N, std::enable_if_t<std::is_integral_v<T> && (N <= 8 / sizeof(T))>>
  {
    using type = neon64_;
  };
#endif
}

#endif
