//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_REBINDABLE_HPP_INCLUDED
#define EVE_CONCEPT_REBINDABLE_HPP_INCLUDED

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

#endif
