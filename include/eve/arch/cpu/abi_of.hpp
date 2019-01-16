//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_CPU_ABI_OF_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>

namespace eve::ext
{
  template<typename Type, int Cardinal, typename EnableIf>
  struct abi_of
  {
    using type = ::eve::emulated_;
  };
}

#endif
