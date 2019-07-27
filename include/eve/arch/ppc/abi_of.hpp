//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_PPC_ABI_OF_HPP_INCLUDED

#include <eve/arch/ppc/predef.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve
{
  struct ppc_;
}

namespace eve::ext
{
#if EVE_HW_POWERPC >= EVE_VMX_VERSION
  template<int N>
  struct abi_of<float, N, std::enable_if_t<(N <= 4)>>
  {
    using type = ::eve::ppc_;
  };

  template<typename T, int N>
  struct abi_of<T,
                N,
                std::enable_if_t<std::is_integral_v<T> && (sizeof(T) < 8) && (N <= 16 / sizeof(T))>>
  {
    using type = ::eve::ppc_;
  };
#endif

#if EVE_HW_POWERPC >= EVE_VSX_VERSION
  template<int N>
  struct abi_of<double, N, std::enable_if_t<(N <= 2)>>
  {
    using type = ::eve::ppc_;
  };

  template<typename T, int N>
  struct abi_of<T, N, std::enable_if_t<std::is_integral_v<T> && (sizeof(T) == 8) && (N <= 2)>>
  {
    using type = ::eve::ppc_;
  };
#endif
}

#endif
