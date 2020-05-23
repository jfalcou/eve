//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BIT_SELECT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BIT_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct bit_select_; }

  template<>
  struct supports_conditionnal<tag::bit_select_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(bit_select_, bit_select);
}

#endif
