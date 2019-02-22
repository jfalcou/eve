//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_ABI_OF_HPP_INCLUDED
#define EVE_EXT_ABI_OF_HPP_INCLUDED

namespace eve
{
  template<typename T>
  struct logical;

  namespace ext
  {
    template<typename Type, int Cardinal, typename EnableIf = void>
    struct abi_of;

    template<typename Type, int Cardinal>
    struct abi_of<logical<Type>, Cardinal> : abi_of<Type, Cardinal>
    {
    };

    template<typename Type, int Cardinal>
    using abi_of_t = typename abi_of<Type, Cardinal>::type;
  }
}

#include <eve/arch/abi_of.hpp>

#endif
