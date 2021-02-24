//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <utility>

namespace eve
{
  template<typename T> concept rebindable = requires(T a)
  {
    { std::tuple_size<T>::value  };
    { ::std::tuple_element_t<0,T>() };
    //{ get<0>(a) };
  };
}

