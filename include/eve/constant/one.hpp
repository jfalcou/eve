//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ONE_HPP_INCLUDED
#define EVE_CONSTANT_ONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(one_, one_);

  template<typename T>
  EVE_FORCEINLINE auto One(as_<T> const & = {})
  {
    return T(1);
  }

  EVE_MAKE_NAMED_CONSTANT(one_, One);
}

#endif
