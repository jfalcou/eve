//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_AS_ARITHMETIC_HPP_INCLUDED
#define EVE_AS_ARITHMETIC_HPP_INCLUDED

#include <eve/forward.hpp>
#include <eve/logical.hpp>

namespace eve
{
  template<typename T>
  struct as_arithmetic
  {
    using type = T ;
  };

  template<>
  struct as_arithmetic < bool >
  {
    using type = bool ;
  };

  template<typename T>
  struct as_arithmetic<logical<T>>
  {
    using type = T;
  };

  template<typename T>
  using as_arithmetic_t = typename as_arithmetic<T>::type;
}

#endif
