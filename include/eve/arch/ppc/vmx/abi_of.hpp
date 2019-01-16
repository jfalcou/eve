//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VMX_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_PPC_VMX_ABI_OF_HPP_INCLUDED

#include <eve/arch/ppc/vmx/tags.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve::ext
{
  template<int N> struct abi_of<float , N, std::enable_if_t<(N<=4)>>  { using type = ::eve::ppc_; };

  template<typename T, int N>
  struct abi_of < T, N
                , std::enable_if_t<std::is_integral_v<T> && (sizeof(T)<8) && (N <= 16/sizeof(T))>
                >
  {
    using type = ::eve::ppc_;
  };
}

#endif
