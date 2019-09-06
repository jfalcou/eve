//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_ORDERED_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_ORDERED_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_DECLARE_TAG(is_ordered_)

  template<>
  struct supports_conditionnal<tag::is_ordered_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_ordered_, is_ordered);
}

#endif
