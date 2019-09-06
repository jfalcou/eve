//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_NEGATIVE_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_NEGATIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct is_negative_; }

  template<>
  struct supports_conditionnal<tag::is_negative_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_negative_, is_negative);
}

#endif
