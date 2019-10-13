//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_DIST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_DIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>


namespace eve
{
  EVE_MAKE_CALLABLE(dist_, dist);
}

#endif
