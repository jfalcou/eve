//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct is_greater_equal_; }

  template<>
  struct supports_conditionnal<tag::is_greater_equal_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_greater_equal_, is_greater_equal);
}

#endif
