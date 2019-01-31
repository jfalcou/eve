//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SATURATED_HPP_INCLUDED
#define EVE_FUNCTION_SATURATED_HPP_INCLUDED

#include <eve/detail/decorator.hpp>

namespace eve
{
  struct saturated_tag
  {
  };
  constexpr inline detail::decorator<saturated_tag> saturated_ = {};
}

#endif
