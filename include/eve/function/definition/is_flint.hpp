//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_FLINT_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_FLINT_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct is_flint_; }

  template<>
  struct supports_conditionnal<tag::is_flint_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_flint_, is_flint);
}

#endif
