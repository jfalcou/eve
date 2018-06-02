//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_EXT_AS_REGISTER_HPP_INCLUDED
#define EVE_EXT_AS_REGISTER_HPP_INCLUDED

#include <array>

namespace eve { namespace ext
{
  template< typename Type, int Cardinal, typename ABI
          , typename EnableIf = void
          >
  struct as_register;

  template< typename Type, int Cardinal, typename ABI>
  using as_register_t = typename as_register<Type,Cardinal,ABI>::type;
} }

#endif
