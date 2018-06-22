//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AS_PACK_HPP_INCLUDED
#define EVE_EXT_AS_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/forward.hpp>

namespace eve
{
  template<typename T> struct logical;

  namespace ext
  {
    template< typename Type, typename Size, typename EnableIf = void>
    struct as_pack
    {
      using type = eve::pack<Type,Size>;
    };

    template< typename Type, typename Size>
    using as_pack_t = typename as_pack<Type,Size>::type;
  }
}

#endif
