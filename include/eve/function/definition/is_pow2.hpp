//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_IS_POW2_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_IS_POW2_HPP_INCLUDED

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct is_pow2_; }

  template<>
  struct supports_conditionnal<tag::is_pow2_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_pow2_, is_pow2);
}

#endif
