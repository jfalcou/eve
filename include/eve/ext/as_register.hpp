//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AS_REGISTER_HPP_INCLUDED
#define EVE_EXT_AS_REGISTER_HPP_INCLUDED

namespace eve::ext
{
  template< typename Type, typename Cardinal, typename ABI
          , typename EnableIf = void
          >
  struct as_register;

  template< typename Type, typename Cardinal, typename ABI>
  using as_register_t = typename as_register<Type,Cardinal,ABI>::type;
}

#include <eve/arch/as_register.hpp>

#endif
