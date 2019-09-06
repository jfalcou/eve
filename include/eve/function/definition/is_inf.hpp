//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_INF_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_INF_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_DECLARE_TAG(is_inf_)

  template<>
  struct supports_conditionnal<tag::is_inf_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_inf_, is_inf);
}

#endif
