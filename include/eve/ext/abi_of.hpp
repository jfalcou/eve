//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_ABI_OF_HPP_INCLUDED

namespace eve { namespace ext
{
  template< typename Type, int Cardinal
          , typename EnableIf = void
          >
  struct abi_of;

  template< typename Type, int Cardinal>
  using abi_of_t = typename abi_of<Type,Cardinal>::type;
} }

#endif
