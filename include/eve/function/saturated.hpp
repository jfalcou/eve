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

namespace eve
{
  namespace decorator { struct saturated_ {}; }

  constexpr inline decorator::saturated_ saturated_ = {};
}

#endif
